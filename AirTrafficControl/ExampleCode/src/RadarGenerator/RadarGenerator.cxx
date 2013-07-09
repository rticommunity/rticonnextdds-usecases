/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef WIN32
#include <direct.h>
#endif 

#include "RadarInterface.h"
#include "TrackGenerator.h"
#include "RadarApp.h"

using namespace DDS;
using namespace std;
using namespace com::rti::atc::generated;

// ------------------------------------------------------------------------- //
//
// Radar Generator Application:
// This application is composed of two main parts:
// 1. The radar generator, which provides example (fake) track data to the 
//    application, and can be given flight plans that it will "correlate" 
//    with individual tracks
// 2. The network interface which:
//    2.1 receives flight plan information and 
//    2.2 sends the track data 
//
//  This application can be started with several parameters to indicate:
//  1. The ID of the radar, which becomes a part of the data, and in the real
//     world would allow receiving applications to correlate the data between
//     multiple sensors.  If unspecified, this is 0
//  2. The maximum number of tracks this application can use at once.  If 
//     unspecified, this is 64.
//  3. The sample rate for how fast this should publish tracks, in 
//     milliseconds.  Default is 100.
//
// ------------------------------------------------------------------------- //

int main(int argc, char *argv[])	
{
    int radarId = 0;
	int sec = 0;
	int sendRate = 1;
	int maxTracks = 64;
	string setting;
	RadarProfile profileToUse = LOW_LATENCY;
	bool multicastAvailable = true;

	for (int i = 0; i < argc; i++)
	{
		if (0 == strcmp(argv[i], "--high-throughput"))
		{
			profileToUse = HIGH_THROUGHPUT;
		} else if (0 == strcmp(argv[i], "--low-latency"))
		{
			profileToUse = LOW_LATENCY;
		} else if (0 == strcmp(argv[i], "--radar-id"))
		{
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass a radar ID" << endl;
				return -1;
			}
			radarId = atoi(argv[i]);
		} else if (0 == strcmp(argv[i], "--max-tracks"))
		{
			// How many tracks can I handle?  Increasing this number will allow the 
			// generator and the middleware to process more tracks.
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass a maximum number of tracks" 
						<< endl;
				return -1;
			}
			maxTracks = atoi(argv[i]);
		} else if (0 == strcmp(argv[i], "--send-rate"))
		{
			// Should I be sending these in real time, faster, or slower?
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass a send rate" 
						<< endl;
				return -1;
			}
			sendRate = atoi(argv[i]);
		} else if (0 == strcmp(argv[i], "--no-multicast"))
		{
			multicastAvailable = false;
		}

	}

	// Tune the radar for low latency.  The two QoS profiles are 
	// defined in USER_QOS_PROFILES.xml
	vector<string> xmlFiles;

	if (multicastAvailable)
	{
		// Adding the XML files that contain profiles used by this application
		xmlFiles.push_back(
			"file://../../../src/Config/base_profile_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/radar_profiles_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/flight_plan_profiles_multicast.xml");
	}
	else 
	{
		// Adding the XML files that contain profiles used by this application
		xmlFiles.push_back(
			"file://../../../src/Config/base_profile_no_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/radar_profiles_no_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/flight_plan_profiles_no_multicast.xml");
	}

	TrackGenerator *trackGenerator = NULL;
	try 
	{ 

		// This sets up the data interface for the radar - what data it sends
		// and receives over the network, along with the quality of service
		RadarInterface *radarNetInterface
					= new RadarInterface(radarId, maxTracks,
								profileToUse, xmlFiles);


		// What is the maximum number of tracks you want to generate?  At what 
		trackGenerator = new TrackGenerator(radarId, maxTracks, sendRate);

		// Create a listener that will react when the track generator gives us
		// track data. In this case, the listener will use the radar writer to
		// write data when track data becomes available.
		DDSRadarListener *radarListener = new DDSRadarListener(
			radarNetInterface->GetRadarWriter(), radarId);

		// Adding a listener to the "track generator" that gets updates about 
		// tracks being generated
		trackGenerator->AddListener(radarListener);

		// Start generating tracks
		trackGenerator->Start();

		while (1) 
		{
			// Listen for updates to flight plans, and add them to the track 
			// generator as they arrive
			vector< DdsAutoType<FlightPlan> > flightPlans;
			radarNetInterface->
				GetFlightPlanReader()->WaitForFlightPlans(&flightPlans);

			for (vector< DdsAutoType<FlightPlan> >::iterator it = flightPlans.begin(); 
				it != flightPlans.end(); it++) 
			{

				// Get flight plan data, and add it to the 
				GeneratorFlightPlan flightPlan;

				// Adapt between the network format of data and the generator
				// format for flight plan data (in this example, we use only
				// the flight ID from the flight plan)
				RadarAdapter::AdaptToGeneratorFlightPlan(flightPlan, (*it));

				// Tell the track generator that this flight plan exists
				trackGenerator->AddFlightPlan(&flightPlan);
			}
		}

		// Remove the listener from the track generator to prevent crashes
		trackGenerator->RemoveListener(radarListener);

		// Shut down the track generator
		trackGenerator->Shutdown();

		// Delete the track generator
		delete trackGenerator;
		delete radarNetInterface;

	}
	catch (string message) 
	{
		cout << "Application exception " << message << endl;
	}


	return 0;
}


