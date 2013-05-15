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

// The way that ATC works in the real world, a flight plan is registered 
// hours in advance of a flight, and it is sent to the appropriate interested
// applications.  It is updated if the plan needs to change for some reason.
// 
// This application creates a number of flight plans, based on the argument to
// the application.  It creates the flight plans for a variety of airlines, and
// sends them.  

// Right now, this is deleting all flight plans after 2 minutes, regardless of
// what the other application does. 
int main(int argc, char *argv[])
{

	int numFlightPlans = 1;
	int timeBetweenLandings = 5; // Five minutes
	if (argc >= 2) {
        numFlightPlans = atoi(argv[1]);
    }
	if (argc >= 3) {
        timeBetweenLandings = atoi(argv[2]);
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
		FlightPlanPublisherInterface fpInterface(xmlFiles);


		DDS_Duration_t send_period = {0,100000000};

		while (1) {

			list<FlightPlan *> flightPlans;
			int i = 0;
// TODO:  Better comment this
			// Write all flight plans
			for (int i = 0; i < numFlightPlans; i++) {
				FlightPlan *plan = FlightPlanTypeSupport::create_data();
				flightPlans.push_back(plan);
				sprintf(plan->flightId, "%s%d", 
					airlines[i % airlineNum], i + 1); 
				sprintf(plan->departureAerodrome, "%s", departureAerodromes[i%8]);
				sprintf(plan->destinationAerodrome, "%s", "KSFO");
				DDS_Time_t time;
				fpInterface.GetParticipant()->get_current_time(time);
				unsigned long currDay = time.sec % SECONDS_PER_DAY; 
				short currHour = (short)(currDay / SECONDS_PER_HOUR);
				short currMin = (short)((currDay % SECONDS_PER_HOUR) / 
					SECONDS_PER_MIN);

				// In this example, each flight lands 5 minutes after the previous
				// flight
				short minToLanding = (currMin + 
					(timeBetweenLandings * (i + 1)));
				plan->estimatedMinutes = minToLanding % SECONDS_PER_MIN;
				
				long hourTemp = currHour + (minToLanding / SECONDS_PER_MIN);
				hourTemp = hourTemp % HOURS_PER_DAY;
				plan->estimatedHours = (short)hourTemp;
				fpInterface.Write(plan);
				NDDSUtility::sleep(send_period);
			}



			DDS_Duration_t deletion_time = {180,000000000};
			NDDSUtility::sleep(deletion_time);

			// Delete all flight plans from network and from the 
			// system.
			for (int i = 0; i < numFlightPlans; i++) {
				fpInterface.Delete(flightPlans.front());

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

