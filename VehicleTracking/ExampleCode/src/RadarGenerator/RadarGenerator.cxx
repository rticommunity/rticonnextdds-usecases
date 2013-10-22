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

void PrintHelp();

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
    int radarId = 42;
	int sec = 0;
	// Run in real time, faster, or slower
	double runRate = 1;
	// How often are new tracks added?
	int creationRateSec = 120;
	// How many tracks should I start generating initially?
	int startTracks = 20;
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
		} else if (0 == strcmp(argv[i], "--start-tracks"))
		{
			// How many tracks can I handle?  Increasing this number will allow the 
			// generator and the middleware to process more tracks.
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass a number of tracks to " <<
					"generate at startup." 
						<< endl;
				return -1;
			}
			startTracks = atoi(argv[i]);

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
		} else if (0 == strcmp(argv[i], "--run-rate"))
		{
			// Should I be sending these in real time, faster, or slower?
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass a run rate" 
						<< endl;
				return -1;
			}
			runRate = atof(argv[i]);
		}  else if (0 == strcmp(argv[i], "--creation-rate"))
		{
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass creation rate" << endl;
				return -1;
			}
			creationRateSec = atoi(argv[i]);
		} else if (0 == strcmp(argv[i], "--no-multicast"))
		{
			multicastAvailable = false;
		} else if (0 == strcmp(argv[i], "--help"))
		{
			PrintHelp();
			return 0;
		} else if (i > 0)
		{
			// If we have a parameter that is not the first one, and is not 
			// recognized, return an error.
			cout << "Bad parameter: " << argv[i] << endl;
			PrintHelp();
			return -1;
		}

	}

	// Set up paths for XML files.  The profiles are for applications that 
	// have no multicast available at all, or that have multicast available
	// on the network.
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


		// Create a new track generator, with a unique ID, a number of tracks
		// to start generating, a maximum number of tracks to generate at a 
		// time, a creation rate (how quickly new tracks are added), and a run
		// rate (real-time, faster, slower)
		trackGenerator = new TrackGenerator(radarId, startTracks, maxTracks, 
			creationRateSec, runRate);

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


void PrintHelp()
{
	cout << "Valid options are: " << endl;
	cout << 
		"    --high-throughput" <<
		"          Use the high throughput XML configuration" 
		<< endl;
	cout << 
		"    --low-latency " <<
		"             Use the low latency XML configuration (default)"
		<< endl;
	cout << 
		"    --radar-id [number]" <<
		"        ID of the radar used to differentiate if there" << 
		"" << endl <<
		"                               " <<
		"are multiple radar generator applications" 
		<< endl;
	cout << 
		"    --start-tracks [number]" <<
		"    Number of tracks the generator should generate at "
		<< "                              " 
		<< "startup" 
		<< endl;
	cout << 
		"    --max-tracks [number]" <<
		"      Maximum tracks the generator sends at once" 
		<< endl;
	cout << 
		"    --run-rate [number]" <<
		"        Run in real time, faster, or slower.  At default"
		<< endl
		<< "                               " 
		<< "rate, all tracks are updated every 100ms.  If "
		<< endl
		<< "                               " 
		<< "you set this to 2 the generator will run twice"
		<< endl
		<< "                               " 
		<< "as fast, updating all tracks every 50ms."
		<< endl;
	cout << 
		"    --creation-rate [number]" <<
		"   How fast to create new tracks in seconds."
		<< endl;
	cout << 
		"    --no-multicast" <<
		"             Do not use multicast " << 
		"(note you must edit XML" << endl <<
		"                               " <<
		"config to include IP addresses)" 
		<< endl;

}
