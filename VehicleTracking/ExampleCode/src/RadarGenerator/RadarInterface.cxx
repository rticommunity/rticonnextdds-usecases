/*
 * (c) 2021 Copyright, Real-Time Innovations, Inc. (RTI) All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the software solely for use with RTI Connext DDS.  Licensee may
 * redistribute copies of the software provided that all such copies are
 * subject to this license. The software is provided "as is", with no warranty
 * of any type, including any warranty for fitness for any purpose. RTI is
 * under no obligation to maintain or support the software.  RTI shall not be
 * liable for any incidental or consequential damages arising out of the use or
 * inability to use the software.
 */

#include <vector>
#include <sstream>
#include "../Generated/AirTrafficControl.hpp"
#include "RadarInterface.h"
#include "GeneratorAdapter.h"


// ------------------------------------------------------------------------- //
// The RadarInterface is the network interface to the whole application.  This
// creates DataReaders and DataWriters in order to receive and send data.
//
// This interface is built from:
// 1. Network data types and topic names defined in the IDL file
// 2. XML configuration files that describe the QoS profiles that should be
//    used by individual DataWriters and DataReaders.  These describe the
//    movement and persistence characteristics of the data (how reliable should
//    this be?), as well as other QoS such as resource limits.
// 3. The code itself creates DataReaders and DataWriters, and selects which
//    profile to use when creating the DataReaders and DataWriters.
//
// Writing radar data:
// -------------------
// This application sends radar data, either with the lowest possible latency
// or with higher throughput at a slight cost in latency.
//
// For information on the radar data type, please see the AirTrafficControl.idl
// file.
//
// For information on the quality of service for throughput vs. latency, please
// see the radar_profiles_multicast.xml file.
//
// Reading flight plan data:
// -------------------------
// This application receives flight plan data.  This data is sent less
// frequently, and if it was sent before the radar application was started, it
// must be automatically delivered to the radar at startup.  Becasue of these
// requirements, it has different QoS than the radar data.  This QoS is
// generally described as the QoS for "state data"
//
// For information on the flight plan data type, please see the
// AirTrafficControl.idl file.
//
// For information on the quality of service for flight plan state data, please
// see the flight_plan_profiles.xml file.
// ------------------------------------------------------------------------- //


RadarInterface::RadarInterface(
        long radarId,
        int maxFlights,
        enum RadarProfile profile,
        std::vector<std::string> qosFileNames)
{
    _radarId = radarId;
    _maxFlightsToHandle = maxFlights;


    std::string libName;
    std::string profileName;

    // Depending on what is passed in, choose one of two XML profiles to
    // use - either for best latency or higher throughput.  Note that the
    // profile string is a constant defined in the .idl file.
    libName = com::atc::generated::QOS_LIBRARY;
    if (profile == LOW_LATENCY) {
        profileName = com::atc::generated::QOS_PROFILE_RADAR_LOW_LATENCY;
    } else if (profile == HIGH_THROUGHPUT) {
        profileName = com::atc::generated::QOS_PROFILE_RADAR_HIGH_THROUGHPUT;
    }

    // This creates the DomainParticpant, the first step in creating a DDS
    // application.  This starts the discovery process.
    rti::core::QosProviderParams provider_name;
    provider_name.url_profile(qosFileNames);
    dds::core::QosProvider::Default().extensions().default_provider_params(
            provider_name);
    dds::core::QosProvider::Default()->default_profile(
            libName + "::" + profileName);


    // Creating the application's RadarWriter object.
    // This could use the RTI Connext DDS writer directly as a way to write,
    // but this example assumes that you are converting between an internal
    // data structure and the network data structure.  If you are not doing
    // this, you can simplifythe logic a bit by giving the applications direct
    // access to the DDS DataWriter class.
    // Note that this might be created with one of two separate XML QoS
    // profiles depending on the requirement for lowest latency or higher
    // throughput at the cost of latency. To see the individual QoS tuning,
    // refer to the XML file.
    _radarWriter = new RadarWriter(this, libName, profileName);
    if (_radarWriter == NULL) {
        std::stringstream errss;
        errss << "Failed to create RadarWriter object";
        throw errss.str();
    }


    // Creating the FlightPlanReader object.
    // We could give the application access to the DataReader directly, but
    // this simplifies the application's access - in this case, we can choose
    // to let the application store the data in the DataReader's queue, and
    // query it directly from the DataReader but we create an object to hide
    // that decision from the user.
    // Initialize the receiver with the QoS profile defined in the
    // flight_plan_profiles_multicast.xml file
    _flightPlanReader = new FlightPlanReader(
            this,
            com::atc::generated::QOS_LIBRARY,
            com::atc::generated::QOS_PROFILE_FLIGHT_PLAN);

    if (_flightPlanReader == NULL) {
        std::stringstream errss;
        errss << "Failed to create FlightPlanReader object";
        throw errss.str();
    }
}

// ------------------------------------------------------------------------- //
// Deleting the Radar Writer, the Flight Plan Reader, and the communicator
// infrastructure.
RadarInterface::~RadarInterface()
{
}

// ------------------------------------------------------------------------- //
// Create the Radar DataWriter.
RadarWriter::RadarWriter(
        RadarInterface* netInterface,
        const std::string& qosLibrary,
        const std::string& qosProfile)
{
    if (netInterface == NULL) {
        std::stringstream errss;
        errss << "RadarWriter(): Bad parameter \"netInterface\"";
        throw errss.str();
    }

    _communicator = netInterface;

    dds::domain::DomainParticipant participant = dds::domain::find(0);
    if (participant == dds::core::null) {
        participant = dds::domain::DomainParticipant(0);
    }

    // The topic object is the description of the data that you will be
    // sending. It associates a particular data type with a name that
    // describes the meaning of the data.  Along with the data types, and
    // whether your application is reading or writing particular data, this
    // is the data interface of your application.

    // This topic has the name AIR_TRACK_TOPIC - a constant string that is
    // defined in the .idl file.  (It is not required that you define your
    // topic name in IDL, but it is a best practice for ensuring the data
    // interface of an application is all defined in one place.
    // Generally you can register all topics and types up-front if
    // necessary.

    // This can be done at any time before creating the DataWriters and
    // DataReaders.  In some systems, this is done in a separate initialization
    // all at once - especially in applications that read and write the same
    // topic
    auto topic = dds::topic::Topic<com::atc::generated::Track>(
            participant,
            com::atc::generated::AIR_TRACK_TOPIC);

    // Create a DataWriter
    // The topic object is the description of the data that you will be
    // sending. It associates a particular data type with a name that
    // describes the meaning of the data.  Along with the data types, and
    // whether your application is reading or writing particular data, this
    // is the data interface of your application.

    // This topic has the name AIR_TRACK_TOPIC - a constant string that was
    // defined in the .idl file.  (It is not required that you define your
    // topic name in IDL, but it is a best practice for ensuring the data
    // interface of an application is all defined in one place.
    // Generally you can register all topics and types up-front if
    // necessary.

    // Start with QoS gathered from the XML file, then update the value of
    // the max_samples and max_instances before creating the DataWriter
    dds::pub::qos::DataWriterQos qos =
            dds::core::QosProvider::Default()->datawriter_qos(
                    qosLibrary + "::" + qosProfile);
    qos << dds::core::policy::ResourceLimits().max_instances(
            _communicator->GetMaxFlightsToHandle());
    qos << dds::core::policy::ResourceLimits().max_samples(
            _communicator->GetMaxFlightsToHandle());
    qos << dds::core::policy::ResourceLimits()->initial_samples(
            _communicator->GetMaxFlightsToHandle());
    qos << dds::core::policy::ResourceLimits()->initial_instances(
            _communicator->GetMaxFlightsToHandle());
    if (_communicator->GetMaxFlightsToHandle()
        < rti::core::policy::RtpsReliableWriterProtocol()
                  .heartbeats_per_max_samples()) {
        qos << rti::core::policy::DataWriterProtocol().rtps_reliable_writer(
                rti::core::policy::RtpsReliableWriterProtocol()
                        .heartbeats_per_max_samples(
                                _communicator->GetMaxFlightsToHandle()));
    }

    _trackWriter = dds::pub::DataWriter<com::atc::generated::Track>(
            dds::pub::Publisher(participant),
            topic,
            qos);
}

// ------------------------------------------------------------------------- //
// Delete the RadarWriter, and the DDS entities using DDS mechanisms - use
// the factory that created the DataWriter to delete the DataWriter
RadarWriter::~RadarWriter()
{
}

// ------------------------------------------------------------------------- //
// Write the data into the DDS "cloud" - in other words, write the data,
// within the numbered domain that the DomainParticipant was created with,
// to whichever DataReaders of the same topic were discovered over the
// available transports.
void RadarWriter::PublishTrack(com::atc::generated::Track& track)
{
    // Write the track data onto the network (or over shared memory)
    _trackWriter.write(track);
}


// ------------------------------------------------------------------------- //
// Deletes the track from the DDS system - this is used to indicate that it
// has landed, and the system does not need to keep track of it any more.
void RadarWriter::DeleteTrack(com::atc::generated::Track& track)
{
    // Retrieve the handle of the instance we were disposing
    // handle = _trackWriter->lookup_instance(track);
    dds::core::InstanceHandle handle = _trackWriter.lookup_instance(track);

    // Note that DDS has two ways to indicate that an instance has gone away
    // it can unregister the instance or dispose it.  Also, by default when
    // the DataWriter unregisters an instance, it also disposes it.  If you
    // dispose and instance, the memory for the instance is not cleaned up,
    // with the expectation that it will be reused.  In this case, the
    // instance IDs will always be recycled, so it is okay to dispose the
    // instance instead of unregistering it.
    _trackWriter.dispose_instance(handle);
}

// ------------------------------------------------------------------------- //
// This creates the DDS DataReader that receives updates about flight plans.
FlightPlanReader::FlightPlanReader(
        RadarInterface* comm,  // Subscriber *sub,
        const std::string& qosLibrary,
        const std::string& qosProfile)
{
    if (comm == NULL) {
        std::stringstream errss;
        errss << "FlightPlanReader(): bad parameter \"comm\"";
        throw errss.str();
    }

    _communicator = comm;
    dds::domain::DomainParticipant participant = dds::domain::find(0);
    if (participant == dds::core::null) {
        participant = dds::domain::DomainParticipant(0);
    }

    // Creating a Topic
    // The topic object is the description of the data that you will be
    // sending. It associates a particular data type with a name that
    // describes the meaning of the data.  Along with the data types, and
    // whether your application is reading or writing particular data, this
    // is the data interface of your application.

    // This topic has the name AIRCRAFT_FLIGHT_PLAN_TOPIC - a constant string
    // that is defined in the .idl file.  (It is not required that you define
    // your topic name in IDL, but it is a best practice for ensuring the data
    // interface of an application is all defined in one place.
    // Generally you can register all topics and types up-front if
    // necessary.
    auto topic = dds::topic::Topic<com::atc::generated::FlightPlan>(
            participant,
            com::atc::generated::AIRCRAFT_FLIGHT_PLAN_TOPIC);


    // Creating a DataReader
    // This DataReader will receive the flight plan. The application will
    // remove the flight plan data from the middleware's queue as it attaches
    // the flight ID to a particular radar track.
    dds::sub::qos::DataReaderQos qos =
            dds::core::QosProvider::Default()->datareader_qos(
                    qosLibrary + "::" + qosProfile);
    _reader = dds::sub::DataReader<com::atc::generated::FlightPlan>(
            dds::sub::Subscriber(participant),
            topic,
            qos);


    // Use this status condition to wake up the thread when data becomes
    // available
    status_cond = new dds::core::cond::StatusCondition(_reader);
    status_cond->enabled_statuses(dds::core::status::StatusMask(
            dds::core::status::StatusMask::data_available()));

    // Attaching the condition to the WaitSet
    _waitSet += *status_cond;
}

// ------------------------------------------------------------------------- //
// Destory the flight plan DataReader and WaitSet.  Note that this uses
// the DDS factories that created various objects to later delete them.
FlightPlanReader::~FlightPlanReader()
{
}

// This example is using an application thread to be notified when flight plans
// arrive.
//
// There are three options for getting data from RTI Connext DDS:
// 1. Being notified in the application's thread of data arriving (as here).
//    This mechanism has slightly higher latency than option #2, but low
//    latency is not important for this use case.  In addition, this is safer
//    than using option #2, because you do not have to worry about the effect
//    on the middleware's thread.
// 2. Being notified in a listener callback of data arriving.
//    This has lower latency than using a WaitSet, but is more dangerous
//    because you have to worry about not blocking the middleware's thread.
// 3. Polling for data.
//    You can call read() or take() at any time to view or remove the data that
//    is currently in the queue.

void FlightPlanReader::WaitForFlightPlans(
        std::vector<com::atc::generated::FlightPlan>* plans)
{
    // Process flight plans if they exist, and do not wait for another
    // notification of new data
    if (true == ProcessFlightPlans(plans)) {
        return;
    }

    // Block thread for flight plan data to arrive
    dds::core::cond::WaitSet::ConditionSeq active_conditions =
            _waitSet.wait(dds::core::Duration::from_secs(1));

    for (uint32_t i = 0; i < active_conditions.size(); i++) {
        if (active_conditions[i] == *status_cond) {
            // If we have been woken up and notified that there was an event, we
            // can try to process flight plans.  Errors in processing flight
            // plans will throw an exception
            ProcessFlightPlans(plans);
        }
    }
}

// This method is taking data from the middleware's queue.
//
// In this example, we remove the data from the middleware's queue by calling
// take().  We do this to illustrate the common case where the data must be
// changed from one format (the network format) to another (the format that the
// radar library expects to receive its flight plan data).
// If the application is able to use the data directly without converting it to
// a different format, you can call read().  This leaves the data in the queue,
// and lets the application access it without having to copy it.

bool FlightPlanReader::ProcessFlightPlans(
        std::vector<com::atc::generated::FlightPlan>* plans)
{
    bool havePlans = false;

    // This call removes the data from the middleware's queue
    dds::sub::LoanedSamples<com::atc::generated::FlightPlan> samples =
            _reader.take();

    // Note, based on the QoS profile (history = keep last, depth = 1) and the
    // fact that we modeled flights as separate instances, we can assume there
    // is only one entry per flight.  So if a flight plan for a particular
    // flight has been changed 10 times, we will  only be maintaining the most
    // recent update to that flight plan in the middleware queue.
    for (dds::sub::LoanedSamples<com::atc::generated::FlightPlan>::iterator
                 sample_it = samples.begin();
         sample_it != samples.end();
         ++sample_it) {
        // Data may not be valid if this is a notification that an instance
        // has changed state.  In other words, this could be a notification
        // that a writer called "dispose" to notify the other applications
        // that the flight plan has moved to a dispose state.
        if (sample_it->info().valid()) {
            // Return a value of true that flight plans have been received
            havePlans = true;
            plans->push_back(sample_it->data());
        }
    }

    return havePlans;
}
