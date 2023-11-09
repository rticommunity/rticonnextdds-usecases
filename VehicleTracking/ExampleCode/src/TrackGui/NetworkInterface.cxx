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

#include "NetworkInterface.h"

// ----------------------------------------------------------------------------
// This creates the NetworkInterface object.

// The NetworkInterface is comprised of:
// 1) One DDSCommunicator object - which is responsible for creating all
//    objects that may be shared by multiple DataWriters and DataReaders -
//    essentially all the objects that are (usually) created only once,
//    regardless of how many data streams the application is sending or
//    receiving.
//    The objects that are (usually) created once generally include:
//      1) DomainParticipant objects.  Typically an application has only one,
//         unless it must communicate in multiple domains.
//      2) Publisher and/or Subscriber.  Typically an application has at most
//	       one of each.
//      3) Topics.  A topic with a particular name may be created only once per
//         DomainParticipant, and can be shared between multiple DataWriters
//         and DataReaders.
//      4) Types.  These must be registered and unregistered exactly once with
//         the DomainParticipant.
// 2) Any DataWriters and DataReaders that comprise the network interface
//    of the application.
NetworkInterface::NetworkInterface(std::vector<std::string> qosFileNames)
{
    // This creates the DomainParticpant, the first step in creating a DDS
    // application.  This starts the discovery process.
    rti::core::QosProviderParams provider_name;
    provider_name.url_profile(qosFileNames);
    dds::core::QosProvider::Default().extensions().default_provider_params(
            provider_name);
    dds::core::QosProvider::Default()->default_profile(
            com::atc::generated::QOS_LIBRARY
            + "::" + com::atc::generated::QOS_PROFILE_RADAR_HIGH_THROUGHPUT);

    dds::domain::DomainParticipant participant(0);

    // Create the DataReader that receives flight plan data.  The profiles
    // that are passed in define how the application will receive data,
    // and how much data will be kept by the middleware.  Look at the
    // associated XML files for details. (Profile names are constant
    // strings pre-defined in the .idl file)
    _flightPlanReader = new FlightPlanReader(
            this,
            com::atc::generated::QOS_LIBRARY,
            com::atc::generated::QOS_PROFILE_FLIGHT_PLAN);

    // Create the DataReader that receives track data.  The profiles
    // that are passed in define how the application will receive data,
    // and how much data will be kept by the middleware.  Look at the
    // associated XML files for details. (Profile names are constant
    // strings pre-defined in the .idl file)
    _trackReader = new TrackReader(
            this,
            com::atc::generated::QOS_LIBRARY,
            com::atc::generated::QOS_PROFILE_RADAR_HIGH_THROUGHPUT);
}

// ----------------------------------------------------------------------------
// Destructor for the network interface. This deletes the readers, and the
// communicator.  Notice that the DDS-specific cleanup code is in the
// destructors of the individual reader and communicator objects.
NetworkInterface::~NetworkInterface()
{
    // Wake the reader up in case it is waiting for data
    _trackReader->NotifyWakeup();
    _flightPlanReader->NotifyWakeup();

    delete _flightPlanReader;
    delete _trackReader;
}


// ----------------------------------------------------------------------------
// Creating the FlightPlanReader object.
// This creates the DDS DataReader object that receives flight plan data over
// one or more transports, and makes it available to the application.  When the
// DataReader object is first created, it starts the discovery process.  The
// DataReader will start to receive data from DataWriters that are:
//  1) In the same domain
//  2) Have the same topic
//  3) Have compatible types
//  4) Have compatible QoS
// as soon as the discovery process has completed.
FlightPlanReader::FlightPlanReader(
        NetworkInterface* app,
        // Subscriber *sub,
        const std::string& qosLibrary,
        const std::string& qosProfile)
{
    if (app == NULL) {
        std::stringstream errss;
        errss << "FlightPlanReader(): bad parameter \"app\"";
        throw errss.str();
    }

    _app = app;

    dds::domain::DomainParticipant participant = dds::domain::find(0);
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
    // This DataReader will receive the flight plan, and will store that flight
    // plan data in the middleware's queue to be queried by the application
    dds::sub::qos::DataReaderQos qos =
            dds::core::QosProvider::Default()->datareader_qos(
                    qosLibrary + "::" + qosProfile);
    _fpReader = dds::sub::DataReader<com::atc::generated::FlightPlan>(
            dds::sub::Subscriber(participant),
            topic,
            qos);


    // Use this guard condition to wake up the thread waiting for data to
    // notify it that the application is being shut down.
    _waitSet += _shutDownNotifyCondition;

    // Use this status condition to wake up the thread when data becomes
    // available
    dds::core::cond::StatusCondition status_cond(_fpReader);
    status_cond.enabled_statuses(dds::core::status::StatusMask(
            dds::core::status::StatusMask::data_available()));
    _waitSet += status_cond;
}

// ----------------------------------------------------------------------------
// Destroying the FlightPlanReader.
FlightPlanReader::~FlightPlanReader()
{
}


// ----------------------------------------------------------------------------
// This call:
//   1) Queries the queue for flight plan data for flights with the ID equal to
//      flightId
//   2) Copies the value of a single flight plan into the the object that is
//      passed in.  Due to the QoS settings, we know this has a history depth
//      of one, so only the latest flight plan information will be in the
//      DataReader's queue.
void FlightPlanReader::GetFlightPlan(
        const char* flightId,
        com::atc::generated::FlightPlan* plan)
{
    // Create a placeholder with only the key field filled in.  This will be
    // used to retrieve the flight plan instance (if it exists).
    com::atc::generated::FlightPlan flightPlan;
    flightPlan.flightId(flightId);

    // Look up the particular instance
    dds::core::InstanceHandle handle = _fpReader.lookup_instance(flightPlan);

    // Not having a flight plan associated with this radar track is a normal
    // case in this example application.  In a real-world application you may
    // want to throw an exception or return an error in the case where a flight
    // appears that has no associated flight plan.
    if (handle.is_nil()) {
        return;
    }

    // Reading just the data for the flight plan we are interested in
    dds::sub::LoanedSamples<com::atc::generated::FlightPlan> samples =
            _fpReader.select().instance(handle).read();

    for (dds::sub::LoanedSamples<com::atc::generated::FlightPlan>::iterator
                 sample_it = samples.begin();
         sample_it != samples.end();
         ++sample_it) {
        if (sample_it->info().valid()) {
            *plan = sample_it->data();
        }
    }
}

// ----------------------------------------------------------------------------
// This wakes up the WaitSet for the FlightPlan DataReader, in case it is being
// used to wait until data is available.  This is used when shutting down to
// ensure that a thread that is querying data from the middleware will be woken
// up to shut down nicely.
void FlightPlanReader::NotifyWakeup()
{
    _shutDownNotifyCondition.trigger_value(true);  //->set_trigger_value(true);
}

// ----------------------------------------------------------------------------
// Creating the TrackReader object.
// This creates the DDS DataReader object that receives track data over one or
// more transports, and makes it available to the application.  When the
// DataReader object is first created, it starts the discovery process.  The
// DataReader will start to receive data from DataWriters that are:
//  1) In the same domain
//  2) Have the same topic
//  3) Have compatible types
//  4) Have compatible QoS
// as soon as the discovery process has completed.
TrackReader::TrackReader(
        NetworkInterface* app,
        //						Subscriber *sub,
        const std::string& qosLibrary,
        const std::string& qosProfile)
{
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
    auto topic = dds::topic::Topic<com::atc::generated::Track>(
            participant,
            com::atc::generated::AIR_TRACK_TOPIC);

    // Creating a DataReader
    // This DataReader will receive the track data, and will make it available
    // for the application to query (read) or remove (take) from the reader's
    // queue
    dds::sub::qos::DataReaderQos qos =
            dds::core::QosProvider::Default()->datareader_qos(
                    qosLibrary + "::" + qosProfile);
    _reader = dds::sub::DataReader<com::atc::generated::Track>(
            dds::sub::Subscriber(participant),
            topic,
            qos);


    // Use this status condition to wake up the thread when data becomes
    // available

    status_cond = new dds::core::cond::StatusCondition(_reader);
    status_cond->enabled_statuses(dds::core::status::StatusMask(
            dds::core::status::StatusMask::data_available()));
    _waitset += *status_cond;

    // Use this guard condition to wake up the thread waiting for data to
    // notify it that the application is being shut down.
    _waitset += _shutDownNotifyCondition;
}

// ----------------------------------------------------------------------------
// Destroying the TrackReader and the objects that are being used to
// access it, such as the WaitSet and conditions.  Notice that we call
// the DDS API delete_contained_entities() to ensure that all conditions
// associated with the DataReader are destroyed.  Topics are not destroyed by
// this call, because they may be shared across multiple DataReaders and
// DataWriters.
TrackReader::~TrackReader()
{
}

// ----------------------------------------------------------------------------
// This example is using an application thread to be notified when tracks
// arrive.
//
// In this example, we leave the data from the middleware's queue by calling
// read().  We do this to illustrate a case where an object that represents
// the flight information (flight plan + track) can be created from data
// that remains in the middleware's queue.  The middleware is configured
// with QoS that allow old updates of track data to be overwritten, so the
// queue does not grow forever.
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

void TrackReader::WaitForTracks(
        std::vector<com::atc::generated::Track>& tracksUpdated,
        std::vector<com::atc::generated::Track>& tracksDeleted)
{
    dds::core::cond::WaitSet::ConditionSeq active_conditions =
            _waitset.wait(dds::core::Duration::from_millisecs(300));

    for (uint32_t i = 0; i < active_conditions.size(); i++) {
        if (active_conditions[i] == *status_cond) {
            // This leaves the data in the DataReader's queue.  Alternately, can
            // call take() which will remove it from the queue.  Leaving data in
            // the makes sense in this application for two reasons:
            // 1) the QoS allows the overwriting of data in the queue
            // 2) the application wants to always see the latest update of each
            //    instance
            dds::sub::LoanedSamples<com::atc::generated::Track> samples =
                    _reader.read();
            for (dds::sub::LoanedSamples<com::atc::generated::Track>::iterator
                         sample_it = samples.begin();
                 sample_it != samples.end();
                 ++sample_it) {
                // Note, based on the QoS profile (history = keep last, depth =
                // 1) and the fact that we modeled flights as separate
                // instances, we can assume there is only one entry per flight.
                // So if a flight plan for a particular flight has been changed
                // 10 times, we will  only be maintaining the most recent update
                // to that flight plan in the middleware queue.
                if (sample_it->info().valid()) {
                    // DdsAutoType<Track> trackType = trackSeq[i];
                    tracksUpdated.push_back(sample_it->data());
                    std::cout << "Received: " << sample_it->data() << std::endl;
                } else if (
                        sample_it->info().state().instance_state()
                        != dds::sub::status::InstanceState::alive()) {
                    com::atc::generated::Track t;
                    _reader.key_value(t, sample_it->info().instance_handle());
                    tracksDeleted.push_back(t);
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------
// This example is using an application thread to poll for all the existing
// track data inside the middleware's queue.
//
// This goes through two steps:
// 1) read() all ALIVE data from the DataReader.  These are the updates of all
//    the flights that have not landed.  By calling read() we leave the data in
//    the queue, and can access it again later if it is not updated.  After
//    reading the data, we return the loan to the DataReader()
// 2) take() all the NOT_ALIVE data from the DataReader.  These are the updates
//    of flights that have landed.  This removes the deletion notices from the
//    queue.  After taking the data, we return the loan to the DataReader()
//
void TrackReader::GetCurrentTracks(
        std::vector<com::atc::generated::Track>& tracksUpdated,
        std::vector<com::atc::generated::Track>& tracksDeleted)
{
    // This reads all ALIVE track data from the queue.
    dds::sub::LoanedSamples<com::atc::generated::Track> samples =
            _reader.select()
                    .state(dds::sub::status::DataState(
                            dds::sub::status::SampleState::any(),
                            dds::sub::status::ViewState::any(),
                            dds::sub::status::InstanceState::alive()))
                    .read();

    // Note, based on the QoS profile (history = keep last, depth = 1) and the
    // fact that we modeled flights as separate instances, we can assume there
    // is only one entry per flight.  So if a flight plan for a particular
    // flight has been changed 10 times, we will  only be maintaining the most
    // recent update to that flight plan in the middleware queue.

    for (dds::sub::LoanedSamples<com::atc::generated::Track>::iterator
                 sample_it = samples.begin();
         sample_it != samples.end();
         ++sample_it) {
        if (sample_it->info().valid()) {
            tracksUpdated.push_back(sample_it->data());
        }
    }

    // Now we access the queue to look for notifications that tracks have been
    // deleted.  We do not leave this in the queue, but remove the deletion
    // notifications.
    samples = _reader.select()
                      .state(dds::sub::status::DataState(
                              dds::sub::status::SampleState::any(),
                              dds::sub::status::ViewState::any(),
                              dds::sub::status::InstanceState::
                                              not_alive_no_writers()
                                      | dds::sub::status::InstanceState::
                                              not_alive_disposed()))
                      .read();

    for (dds::sub::LoanedSamples<com::atc::generated::Track>::iterator
                 sample_it = samples.begin();
         sample_it != samples.end();
         ++sample_it) {
        // Note, based on the QoS profile (history = keep last, depth = 1) and
        // the fact that we modeled flights as separate instances, we can assume
        // there is only one entry per flight.  So if a flight plan for a
        // particular flight has been changed 10 times, we will  only be
        // maintaining the most recent update to that flight plan in the
        // middleware queue.
        if (sample_it->info().state().instance_state()
            != dds::sub::status::InstanceState::alive()) {
            com::atc::generated::Track t;
            _reader.key_value(t, sample_it->info().instance_handle());
            tracksDeleted.push_back(t);
        }
    }
}

// ----------------------------------------------------------------------------
// This wakes up the WaitSet for the Track DataReader, in case it is being
// used to wait until data is available.  This is used when shutting down to
// ensure that a thread that is querying data from the middleware will be woken
// up to shut down nicely.
void TrackReader::NotifyWakeup()
{
    _shutDownNotifyCondition.trigger_value(true);
}
