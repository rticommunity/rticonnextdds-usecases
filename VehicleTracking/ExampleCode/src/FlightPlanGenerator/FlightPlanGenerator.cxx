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
#include <list>
#include <iostream>
#include <dds/dds.hpp>
#include "../Generated/AirTrafficControl.hpp"


using namespace std;

#define SECONDS_PER_DAY 86400
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MIN 60
#define HOURS_PER_DAY 24

void PrintHelp();

// ------------------------------------------------------------------------- //
//
//
// The way that ATC works in the real world, a flight plan is registered
// hours in advance of a flight, and it is sent to the appropriate interested
// applications.  It is updated if the plan needs to change for some reason.
//
// This application creates a number of flight plans, based on the argument to
// the application.  It creates the flight plans for a variety of airlines, and
// sends them.
//
// The flight plan data is modeled as RTI Connext DDS "state data," meaning:
//   1) the data is modeled to have a key field which differentiates individual
//      flight plans.  This key field is the flight ID.
//   ...and that it is sent:
//   1) Reliably
//   2) Durably - meaning that this application can write a flight plan, and
//      even if the subscribing applications do not exist, yet, they will be
//      notified of all flight plans as soon as they create the corresponding
//      DataReader.
//   3) With a history set to: kind = keep last, depth = 1.  This means that
//      just the most recent update to each flight plan will be sent to
//      DataReaders at startup.
//      Note:  THIS HISTORY SETTING IS NOT APPROPRIATE FOR STRICT RELIABLITY.
//      If you were to rapidly update the same flight plan many times, it is
//      possible that some updates would be overwritten.  This guarantees
//      delivery of the _most recent_ update to the flight plan.
//
// ------------------------------------------------------------------------- //

int main(int argc, char* argv[])
{
    int numFlightPlans = 200;
    int timeBetweenLandings = 5;  // Five minutes
    bool multicastAvailable = true;
    for (int i = 0; i < argc; i++) {
        if (0 == strcmp(argv[i], "--num-plans")) {
            ++i;
            if (i == argc) {
                cout << "Bad parameter: Did not pass number of plans" << endl;
                return -1;
            }
            numFlightPlans = atoi(argv[i]);
        } else if (0 == strcmp(argv[i], "--time-between")) {
            ++i;
            if (i == argc) {
                cout << "Bad parameter: Did not pass time between landing"
                     << endl;
                return -1;
            }
            timeBetweenLandings = atoi(argv[i]);
        } else if (0 == strcmp(argv[i], "--no-multicast")) {
            multicastAvailable = false;
        } else if (0 == strcmp(argv[i], "--help")) {
            PrintHelp();
            return 0;
        } else if (i > 0) {
            // If we have a parameter that is not the first one, and is not
            // recognized, return an error.
            cout << "Bad parameter: " << argv[i] << endl;
            PrintHelp();
            return -1;
        }
    }
    int airlineNum = 35;
    const std::string airlines[] = { "SWA", "VIR", "ACA", "CCA", "SWR", "AAL",
                                     "TRS", "ASA", "ANA", "BAW", "CPA", "CAL",
                                     "CES", "KLM", "JAL", "KAL", "UAL", "DAL",
                                     "EVA", "FFT", "HAL", "LAN", "DLH", "PAL",
                                     "SAS", "UAE", "JBU", "SCX", "VRD", "ANZ",
                                     "SIA", "LRC", "AMX", "THO", "AFR" };

    const std::string departureAerodromes[] = {
        "KDAL", "KLAX", "KSEA", "KEWR", "KBOS", "KDFW", "KDEN", "KJFK"
    };

    // Tune the radar for low latency.  The two QoS profiles are
    // defined in radar_profiles_multicast.xml and
    // radar_profiles_no_multicast.xml
    vector<string> xmlFiles;

    if (multicastAvailable) {
        // Adding the XML files that contain profiles used by this application
        xmlFiles.push_back("file://../src/Config/base_profile_multicast.xml");
        xmlFiles.push_back("file://../src/Config/radar_profiles_multicast.xml");
        xmlFiles.push_back(
                "file://../src/Config/flight_plan_profiles_multicast.xml");
    } else {
        // Adding the XML files that contain profiles used by this application
        xmlFiles.push_back(
                "file://../src/Config/base_profile_no_multicast.xml");
        xmlFiles.push_back(
                "file://../src/Config/radar_profiles_no_multicast.xml");
        xmlFiles.push_back(
                "file://../src/Config/flight_plan_profiles_no_multicast.xml");
    }
    try {
        // Create a DomainParticipant
        // Start by creating a DomainParticipant.  Generally you will have only
        // one DomainParticipant per application.  A DomainParticipant is
        // responsible for starting the discovery process, allocating resources,
        // and being the factory class used to create Publishers, Subscribers,
        // Topics, etc.  Note:  The string constants with the QoS library name
        // and the QoS profile name are configured as constants in the .idl
        // file.  The profiles themselves are configured in the .xml file.

        rti::core::QosProviderParams provider_name;
        provider_name.url_profile(xmlFiles);
        dds::core::QosProvider::Default().extensions().default_provider_params(
                provider_name);
        dds::core::QosProvider::Default()->default_profile(
                com::atc::generated::QOS_LIBRARY
                + "::" + com::atc::generated::QOS_PROFILE_FLIGHT_PLAN);
        dds::domain::DomainParticipant participant(0);

        // Creating a Topic
        // The Topic object is the description of the data that you will be
        // sending. It associates a particular data type with a name that
        // describes the meaning of the data.  Along with the data types, and
        // whether your application is reading or writing particular data, this
        // is the data interface of your application.

        // This topic has the name AIRCRAFT_FLIGHT_PLAN_TOPIC - a constant
        // string that is defined in the .idl file.  (It is not required that
        // you define your topic name in IDL, but it is a best practice for
        // ensuring the data interface of an application is all defined in one
        // place. You can register all topics and types up-front, if you nee
        auto topic = dds::topic::Topic<com::atc::generated::FlightPlan>(
                participant,
                com::atc::generated::AIRCRAFT_FLIGHT_PLAN_TOPIC);


        // Create a DataWriter.
        // This creates a single DataWriter that writes flight plan data, with
        // QoS
        // that is used for State Data.	Note: The string constants with the QoS
        // library name and the QoS profile name are configured as constants in
        // the .idl file.  The profiles themselves are configured in the .xml
        // file.
        dds::pub::qos::DataWriterQos qos =
                dds::core::QosProvider::Default()->datawriter_qos(
                        com::atc::generated::QOS_LIBRARY
                        + "::" + com::atc::generated::QOS_PROFILE_FLIGHT_PLAN);
        dds::pub::DataWriter<com::atc::generated::FlightPlan> writer =
                dds::pub::DataWriter<com::atc::generated::FlightPlan>(
                        dds::pub::Publisher(participant),
                        topic,
                        qos);


        dds::core::Duration send_period(0, 100000000);

        cout << "Sending flight plans over RTI Connext DDS" << endl;


        // Write all flight plans up to the number specified
        for (int i = 0; i < numFlightPlans; i++) {
            // Allocate a flight plan structure
            com::atc::generated::FlightPlan flightPlan;

            // Give it a random airline and flight ID based on airlines
            // that fly into SFO
            flightPlan.flightId(
                    airlines[i % airlineNum] + std::to_string(i + 1));

            // Give it a departure aerodrome
            flightPlan.departureAerodrome(departureAerodromes[i % 8].c_str());

            // Destination aerodrome is always SFO
            flightPlan.destinationAerodrome("KSFO");

            // Use the current time as a starting point for the expected
            // landing time of the aircraft
            dds::core::Time time = participant.current_time();

            unsigned long currDay = time.sec() % SECONDS_PER_DAY;
            short currHour = (short) (currDay / SECONDS_PER_HOUR);
            short currMin =
                    (short) ((currDay % SECONDS_PER_HOUR) / SECONDS_PER_MIN);

            // In this example, each flight lands 5 minutes after the
            // previous flight
            short minToLanding = (currMin + (timeBetweenLandings * (i + 1)));
            flightPlan.estimatedMinutes(minToLanding % SECONDS_PER_MIN);

            long hourTemp = currHour + (minToLanding / SECONDS_PER_MIN);
            hourTemp = hourTemp % HOURS_PER_DAY;
            flightPlan.estimatedHours((short) hourTemp);

            // Write the data to the network.  This is a thin wrapper
            // around the RTI Connext DDS DataWriter that writes data to
            // the network.
            writer.write(flightPlan);

            rti::util::sleep(send_period);
        }

        while (1) {
            rti::util::sleep(send_period);
        }
    } catch (string message) {
        cout << "Application exception: " << message << endl;
    }


    return 0;
}

void PrintHelp()
{
    cout << "Valid options are: " << endl;
    cout << "    --num-plans [num]"
         << "              Number of flight plans to send" << endl;
    cout << "    --time-between [time in ms]"
         << "    Time between sending flight plans" << endl;
    cout << "    --no-multicast"
         << "                 Do not use multicast "
         << "(note you must edit XML" << endl
         << "                                   "
         << "config to include IP addresses)" << endl;
}
