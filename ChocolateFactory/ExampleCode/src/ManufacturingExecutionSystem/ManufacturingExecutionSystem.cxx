/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#include <vector>
#include <list>
#include <iostream>
#include "../Generated/ChocolateFactory.h"
#include "../CommonInfrastructure/DDSTypeWrapper.h"
#include "../CommonInfrastructure/EnumPrintHelpers.h"
#include "../CommonInfrastructure/OSAPI.h"
#include "MESInterface.h"

using namespace std;

void PrintHelp();
void *PrintLotUpdates(void *param);

// ------------------------------------------------------------------------- //
//
//
// This application writes updates announcing that a chocolate lot is ready to
// be processed.  It fills in the details of the recipe name and the first
// station controller to process the lot, and announces over the network that 
// the lot should be processed.
//
// This also listens for chocolate lot state data so it can print information 
// displaying the chocolate lot state data as the state is updated.
//
// The chocolate lot state data is modeled as RTI Connext DDS "state data," 
// meaning:
//   1) the data is modeled to have a key field which differentiates individual
//      updates of each lot from each station controller.  This key fields are
//      the lot ID and the station controller kind.
//   ...and that it is sent:
//   1) Reliably
//   2) Durably - meaning that this application can write a lot update, and
//      even if the subscribing applications do not exist, yet, they will be
//      notified of all lot updates as soon as they create the corresponding
//      DataReader.
//   3) With a history set to: kind = keep last, depth = 1.  This means that 
//      just the most recent update to each chocolate lot sate will be sent to 
//      DataReaders at startup.  
//      Note:  THIS HISTORY SETTING IS NOT APPROPRIATE FOR STRICT RELIABLITY.
//      If you were to rapidly update the same lot state many times, it is 
//      possible that some updates would be overwritten.  This guarantees 
//      delivery of the _most recent_ update to the lot state.
//
// Note: it is possible to get chocolate lot state updates "out of order,"  
// meaning that you may see an update saying that a particular controller is
// processing the lot and THEN get an update saying it was assigned to that 
// controller.  This is inherent in the fact that you are getting updates from
// multiple sources that could be sending updates from multiple machines.
// ------------------------------------------------------------------------- //

int main(int argc, char *argv[])
{

	int numLotsToProcess = 5;
	int timeBetweenLotCommands = 20; // 20 Seconds
	bool multicastAvailable = true;
	for (int i = 0; i < argc; i++)
	{
		if (0 == strcmp(argv[i], "--num-lots"))
		{
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass number of lots" << endl;
				return -1;
			}
			numLotsToProcess =  atoi(argv[i]);
		} else if (0 == strcmp(argv[i], "--time-between"))
		{
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass number of seconds between lot commands" 
					<< endl;
				return -1;
			}
			timeBetweenLotCommands =  atoi(argv[i]);
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
			"file://../../../src/Config/recipe_profiles_multicast.xml");
	}
	else 
	{
		// Adding the XML files that contain profiles used by this application
		xmlFiles.push_back(
			"file://../../../src/Config/base_profile_no_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/recipe_profiles_no_multicast.xml");
	}

	try 
	{

		// This is the network interface for this application - this is what
		// actually sends the lot state information over the transport 
		// (shared memory or over the network).  Look into this class to see
		// what you need to do to implement an RTI Connext DDS application that
		// reads and writes data.
		MESInterface mesInterface(xmlFiles);

		// Start a thread that will listen for updates about lots as they pass
		// through the different station controllers
		OSThread *thread = new OSThread(
			(ThreadFunction)PrintLotUpdates, &mesInterface);	
		thread->Run();

		DDS_Duration_t send_period = {timeBetweenLotCommands,0};

		cout << "Sending chocolate lot commands over RTI Connext DDS\n" 
			<< endl;
		vector<string> recipeNames;
		recipeNames.push_back("Dark");
		recipeNames.push_back("Milk");
		recipeNames.push_back("White");


		// Write all chocolate lots up to the number specified
		for (int i = 0; i < numLotsToProcess; i++) 
		{

			// Allocate a chocolate lot state
			DdsAutoType<ChocolateLotState> lotState;

			// Give it an ID number
			lotState.lotID = i;

			// Currently this lot is not at a controller
			lotState.controller = INVALID_CONTROLLER;

			// Give it a recipe type: plain dark chocolate, milk chocolate, or
			// white chocolate
			sprintf(lotState.recipeName, "%s", 
				recipeNames[i % 3].c_str()); 

			// All lots must to go the sugar controller first
			lotState.nextController = SUGAR_CONTROLLER;

			// The current lot status is that it is assigned to a station
			// controller.
			lotState.lotStatus = ASSIGNED_TO_SC;
			
			cout << "Sending command to start lot with recipe " << 
				lotState.recipeName << endl;

			// Write the data to the network.  This is a thin wrapper 
			// around the RTI Connext DDS DataWriter that writes data to
			// the network.
			mesInterface.GetChocolateLotStateWriter()->
				PublishChocolateLotState(lotState);

			NDDSUtility::sleep(send_period);
		}

		// Wait for updates about chocolate lots and print out their status
		while (1) 
		{
			NDDSUtility::sleep(send_period);
		}
	}
	catch (string message)
	{
		cout << "Application exception" << message << endl;
	}

	return 0;
}

// ------------------------------------------------------------------------- //
// This function waits for updates to lot states as they arrive over DDS (over
// the network or shared memory).  When it receives updates to lot states, it
// prints the current state of the lot to the screen.
// 
// Note: it is possible to get these updates "out of order," meaning that you 
// may see an update saying that a particular controller is processing the lot
// and THEN get an update saying it was assigned to that controller.  This is 
// inherent in the fact that you are getting updates from multiple sources that
// could be on multiple machines.
void *PrintLotUpdates(void *param)
{
	MESInterface *mesInterface = (MESInterface *)param;

	while (1)
	{
		vector< DdsAutoType<ChocolateLotState> > lotStates;

		// This blocks a thread until chocolate lot state updates become 
		// available over DDS.  It fills in the vector with chocolate lot state
		// updates.
		mesInterface->GetChocolateLotStateReader()->
			WaitForChocolateLotUpdates(&lotStates);

		// Iterate over the chocolate lot state updates that have arrived
		for (int i = 0; i < lotStates.size(); i++)
		{
			string lotStatus, controllerName;

			// Get the name of the lot status to help with printing 
			LotStatusType::GetLotStatusPrettyName(lotStates[i].lotStatus, 
				lotStatus);

			// If the lot is not "assigned to station controller" print the
			// current station controller
			if (lotStates[i].lotStatus != ASSIGNED_TO_SC)
			{
				// Get the name of the current station controller that is
				// updating the state of the chocolatel ot.
				StationControllerType::GetControllerPrettyName(
					lotStates[i].controller,
					controllerName);
			} else
			{
				// If the lot is "assigned to station controller," print the
				// name of the next station controller that it is assigned to
				StationControllerType::GetControllerPrettyName(
					lotStates[i].nextController,
					controllerName);
			}

			cout << "Lot #" << lotStates[i].lotID
				<< " is in state: "
				<< lotStatus.c_str() 
				<< " at controller: "
				<< controllerName.c_str() << endl;

		}
	}
}

void PrintHelp()
{
	cout << "Valid options are: " << endl;
	cout << 
		"    --num-lots [num]" <<
		"              Number of lots to start before shutting down" 
		<< endl;
	cout << 
		"    --time-between [time in ms]" <<
		"    Time between starting lot batches"
		<< endl;
	cout << 
		"    --no-multicast" <<
		"                 Do not use multicast " << 
		"(note you must edit XML" << endl <<
		"                                   " <<
		"config to include IP addresses)" 
		<< endl;

}
