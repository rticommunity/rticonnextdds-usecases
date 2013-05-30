// FlightPlanPublisher.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <list>
#include <iostream>
#include "../Generated/AirTrafficControl.h"
#include "../Generated/AirTrafficControlSupport.h"
#include "FlightPlanPublisherInterface.h"

using namespace std;

#define SECONDS_PER_DAY 86400
#define SECONDS_PER_HOUR 3600
#define SECONDS_PER_MIN 60
#define HOURS_PER_DAY 24

// ------------------------------------------------------------------------- //
//
// The way that ATC works in the real world, a flight plan is registered 
// hours in advance of a flight, and it is sent to the appropriate interested
// applications.  It is updated if the plan needs to change for some reason.
// 
// This application creates a number of flight plans, based on the argument to
// the application.  It creates the flight plans for a variety of airlines, and
// sends them.  
//
// This example application is deleting all flight plans after 2 minutes, 
// regardless of what the other applications do. 
//
// The flight plan data is modeled as RTI Connext DDS "state data," meaning:
//   1) the data is modeled to have a key field which differentiates individual
//      flight plans.  This key field is the flight ID.
//
//   and that it is sent:
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

int main(int argc, char *argv[])
{

	int numFlightPlans = 200;
	int timeBetweenLandings = 5; // Five minutes
	for (int i = 0; i < argc; i++)
	{
		if (0 == strcmp(argv[i], "--num-plans"))
		{
			++i;
			numFlightPlans =  atoi(argv[i]);
		} else if (0 == strcmp(argv[i], "--time-between"))
		{
			++i;
			timeBetweenLandings =  atoi(argv[i]);
		}  

	}
	int airlineNum = 35;
	char *airlines[] = {
		"SWA","VIR", "ACA","CCA","SWR",
		"AAL","TRS","ASA","ANA","BAW",
		"CPA","CAL","CES","KLM","JAL",
		"KAL","UAL","DAL","EVA","FFT",
		"HAL","LAN","DLH","PAL","SAS",
		"UAE","JBU","SCX","VRD","ANZ",
		"SIA","LRC","AMX","THO","AFR"};
	
	char *departureAerodromes[] = {
		"KDAL","KLAX", "KSEA", "KEWR", 
		"KBOS", "KDFW", "KDEN", "KJFK"};

	// Tune the radar for low latency.  The two QoS profiles are 
	// defined in USER_QOS_PROFILES.xml
	vector<string> xmlFiles;

	// Adding the XML files that contain profiles used by this application
	xmlFiles.push_back("file://../src/Config/multicast_base_profile.xml");
	xmlFiles.push_back("file://../src/Config/radar_profiles_multicast.xml");
	xmlFiles.push_back(
		"file://../src/Config/flight_plan_profiles_multicast.xml");

	try {

		// This is the network interface for this application - this is what
		// actually sends the flight plan information over the transport 
		// (shared memory or over the network).  Look into this class to see
		// what you need to do to implement an RTI Connext DDS application that
		// writes data.
		FlightPlanPublisherInterface fpInterface(xmlFiles);


		DDS_Duration_t send_period = {0,100000000};

		printf("Sending flight plans over RTI Connext DDS\n");

		while (1) {

			list<FlightPlan *> flightPlans;
			int i = 0;

			// Write all flight plans
			for (int i = 0; i < numFlightPlans; i++) {

				// Allocate a flight plan structure
				FlightPlan *plan = FlightPlanTypeSupport::create_data();

				// Add it to our vector of flight plans
				flightPlans.push_back(plan);

				// Give it a random airline and flight ID based on airlines
				// that fly into SFO
				sprintf(plan->flightId, "%s%d", 
					airlines[i % airlineNum], i + 1); 

				// Give it a departure aerodrome
				sprintf(plan->departureAerodrome, "%s", 
					departureAerodromes[i%8]);

				// Destination aerodrome is always SFO
				sprintf(plan->destinationAerodrome, "%s", "KSFO");

				// Use the current time as a starting point for the expected
				// landing time of the aircraft
				DDS_Time_t time;
				fpInterface.GetCommunicator()->GetParticipant()
											->get_current_time(time);
				unsigned long currDay = time.sec % SECONDS_PER_DAY; 
				short currHour = (short)(currDay / SECONDS_PER_HOUR);
				short currMin = (short)((currDay % SECONDS_PER_HOUR) / 
					SECONDS_PER_MIN);

				// In this example, each flight lands 5 minutes after the 
				// previous flight
				short minToLanding = (currMin + 
					(timeBetweenLandings * (i + 1)));
				plan->estimatedMinutes = minToLanding % SECONDS_PER_MIN;
				
				long hourTemp = currHour + (minToLanding / SECONDS_PER_MIN);
				hourTemp = hourTemp % HOURS_PER_DAY;
				plan->estimatedHours = (short)hourTemp;

				// Write the data to the network.  This is a thin wrapper 
				// around the RTI Connext DDS DataWriter that writes data to
				// the network.
				fpInterface.Write(plan);

				NDDSUtility::sleep(send_period);
			}



			// Sleep for two minutes after publishing the flight plans
			DDS_Duration_t deletion_time = {180,000000000};
			NDDSUtility::sleep(deletion_time);

			// Delete all flight plans from network and from the system
			for (int i = 0; i < numFlightPlans; i++) {

				// Notify the network that these flight plans are no longer
				// valid.  This is necessary if we want to free up resources
				// associated with the current flight plans.
				fpInterface.Delete(flightPlans.front());

				// Delete the actual flight plan data from the application.
				FlightPlanTypeSupport::delete_data(flightPlans.front());
				flightPlans.pop_front();
				NDDSUtility::sleep(send_period);
			}

		}
	}
	catch (string message)
	{
		cout << "Application exception" << message << endl;
	}


	return 0;
}

