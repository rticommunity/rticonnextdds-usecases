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
#include "StationController.h"
#include "../CommonInfrastructure/EnumPrintHelpers.h"


using namespace DDS;
using namespace std;
using namespace com::rti::chocolatefactory::generated;

void PrintHelp();

// TODO: Update comments
// ------------------------------------------------------------------------- //
//
// Station Controller Application:
// TODO: better comments
//
// ------------------------------------------------------------------------- //

int main(int argc, char *argv[])	
{
	int sec = 0;

	int controllerType = 1;
	string setting;
	bool multicastAvailable = true;

	for (int i = 0; i < argc; i++)
	{

		if (0 == strcmp(argv[i], "--controller-type"))
		{
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass a station controller type" << endl;
				return -1;
			}
			controllerType = atoi(argv[i]);

			// Only curently have 5 types of controller
			if (controllerType < 1 || controllerType > 5)
			{
				cout << "Bad parameter: controller types are between 1 and 5" << endl;
				return -1;
			}
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

		// This sets up the data interface for the station controller - what 
		// data it sends and receives over the network, along with the quality
		// of service
		StationControllerInterface *stationControllerInterface
					= new StationControllerInterface(
								(StationControllerKind)controllerType,
								xmlFiles);

		StationController *controller = new StationController(
			(StationControllerKind)controllerType,
			stationControllerInterface);

		// Process incoming lots
		controller->ProcessLots();

		delete controller;
		delete stationControllerInterface;
	}
	catch (string message) 
	{
		cout << "Application exception " << message << endl;
	}


	return 0;
}


// TODO: Initialize the station controller interface in the constructor?
// ----------------------------------------------------------------------------
// Station controller constructor.  

StationController::StationController(
	StationControllerKind kind,
	StationControllerInterface *scInterface)
{
	_stationControllerKind = kind;
	_networkInterface = scInterface;
	_shuttingDown = false;
}
// ----------------------------------------------------------------------------
// ProcessLots:
// This method executes the main logic for the StationController:
//   1.) wait for lot status
//   2.) process
//   3.) pass to next sc

// TODO: move this to multiple methods?
void StationController::ProcessLots()
{
	while (!_shuttingDown)
	{
		vector<DdsAutoType<ChocolateLotState>> lotsToProcess;
		_networkInterface->
			GetChocolateLotStateReader()->WaitForChocolateLotUpdates(
					&lotsToProcess);

		string controllerKindString;
		GetControllerKind(controllerKindString);
		printf("Station controller %s waiting for data\n", 
			controllerKindString.c_str());

		// Announce that all lots I have received requests for are waiting at
		// this StationController to be processed.
		for (int i = 0; i < lotsToProcess.size(); i++)
		{

			DdsAutoType<ChocolateLotState> updatedState;

			// If this lot is entirely completed with the process of being
			// created, I can unregister it - removing any information that
			// I was storing about its state
			if (lotsToProcess[i].lotStatus == COMPLETED)
			{
				updatedState.lotID = lotsToProcess[i].lotID;
				updatedState.controller = _stationControllerKind;
				_networkInterface->GetChocolateLotStateWriter()->
					UnregisterChocolateLotState(updatedState);
				continue;
			}

			// If this lot is being assigned to me, update its status to say 
			// it is waiting at my station
			if (lotsToProcess[i].assignedLotOwner == _stationControllerKind)
			{
				updatedState.lotID = lotsToProcess[i].lotID;
				updatedState.controller = _stationControllerKind;
 				updatedState.lotStatus = WAITING_AT_SC;
				strcpy(updatedState.recipeName, lotsToProcess[i].recipeName);
				updatedState.assignedLotOwner = _stationControllerKind;

				_networkInterface->GetChocolateLotStateWriter()->
					PublishChocolateLotState(updatedState);
			}
		}

		// Process the lots that we know about.  "Processing" a lot involves
		// just sleeping in place of real functionality
		for (int i = 0; i < lotsToProcess.size(); i++)
		{
			if (lotsToProcess[i].assignedLotOwner == _stationControllerKind
				&& lotsToProcess[i].lotStatus != COMPLETED)
			{
				DdsAutoType<ChocolateLotState> updatedState;
				updatedState.lotID = lotsToProcess[i].lotID;
				updatedState.controller = _stationControllerKind;
 				updatedState.lotStatus = PROCESSING_AT_SC;
				strcpy(updatedState.recipeName, lotsToProcess[i].recipeName);
				updatedState.assignedLotOwner = _stationControllerKind;

				_networkInterface->GetChocolateLotStateWriter()->
					PublishChocolateLotState(updatedState);

				// "Processing" the lot for 2 seconds.  Really only sleeping
				printf("Station controller %s processing lot #%d\n", 
						controllerKindString.c_str(), 
						lotsToProcess[i].lotID);
				DDS_Duration_t busySleep = {2,0};
				NDDSUtility::sleep(busySleep);

				// Who is the next station controller in the recipe?  Query the
				// middleware to get the recipe and then send an update 
				// assigning this lot to the next station
				DdsAutoType<ChocolateRecipe> recipe;
				_networkInterface->GetRecipeReader()->GetRecipe(
					lotsToProcess[i].recipeName, &recipe);

				RecipeStep *steps = new RecipeStep[MAX_RECIPE_STEPS];
				recipe.steps.to_array(steps, recipe.steps.length());

				for (int j = 0; j < MAX_RECIPE_STEPS; j++)
				{
					// Iterate over the recipe until reaching the current step
					// in the process.
					if (steps[j].stationController == _stationControllerKind)
					{
						// If this is the last step in the recipe, we can mark
						// this lot as completed.
						if (j == recipe.steps.length() - 1)
						{
							updatedState.lotStatus = COMPLETED;
							break;
						} else
						{
							// Assign this lot to the next control station in
							// the recipe
							updatedState.assignedLotOwner = 
								steps[j + 1].stationController;
							updatedState.lotStatus = ASSIGNED_TO_SC;
							break;
						}
					}
				}

				string nextControllerKindString;
				StationControllerType::GetControllerPrettyName(
					updatedState.assignedLotOwner, nextControllerKindString);
				printf("Station controller %s sending lot #%d to %s\n", 
						controllerKindString.c_str(), 
						updatedState.lotID,
						nextControllerKindString.c_str());

				// Update to say we are done with lot, and it is time for
				// the next station controller to process it, or that it is 
				// completed.
				_networkInterface->GetChocolateLotStateWriter()->
					PublishChocolateLotState(updatedState);

			}

		}

	}
}


// TODO comment this
void StationController::GetControllerKind(std::string &kindOut)
{
	StationControllerType::GetControllerPrettyName(
		_stationControllerKind, 
		kindOut);
}

void PrintHelp()
{
	cout << "Valid options are: " << endl;
	cout << 
		"    --controller-type [number]" <<
		" Valid values 1-5. Type of controller to use" 
		<< endl;
	cout << 
		"    --no-multicast" <<
		"             Do not use multicast " << 
		"(note you must edit XML" << endl <<
		"                               " <<
		"config to include IP addresses)" 
		<< endl;

}
