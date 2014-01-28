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

// ------------------------------------------------------------------------- //
//
// Station Controller Application:
// This application acts as a "station controller" in a chocolate factory. Its
// purpose is to process a chocolate lot according to a recipe for the chocolate
// either dark chocolate, milk chocolate, or white chocolate.
// 
// To "process" a lot, this application retrieves the recipe that this lot is
// using, and based on how much time the step should take, it sleeps.
//
// This application receives:
//     1. Recipe data: it receives recipes so it can get information on how to
//        process a particular lot.  (Note that this exmaple replaces real 
//        recipe information with how long to sleep)
//     2. Filtered chocolate lot state updates: this application creates a 
//        content-filtered topic, so it receives only updates about chocolate
//        lots that: 
//          a. Are assigned to it, or
//          b. Are completed (so it can unregister that lot)
// 
// This application sends:
//     1. Updates to a chocolate state saying either:
//          a. It is waiting at this station controller
//          b. This station controller is processing it
//          c. It is assigned to the next station controller in the recipe
//          d. It is completed (no more station controllers in the recipe)
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
		// There are five types of valid controller described in the IDL type 
		// StationControllerKind: Sugar controller, cocoa butter controller
		// cocoa liquor controller, vanilla controller, and milk controller
		if (0 == strcmp(argv[i], "--controller-type"))
		{
			++i;
			if (i == argc)
			{
				cout << "Bad parameter: Did not pass a station controller type"
					<< endl;
				return -1;
			}
			controllerType = atoi(argv[i]);

			// Only curently have 5 types of controller
			if (controllerType < 1 || controllerType > 5)
			{
				cout << "Bad parameter: controller types are between 1 and 5" 
					<< endl;
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
		// of service.  From the standpoint of RTI Connext, this is where
		// the most interesting code is that sets up all of the objects that
		// allow the application to communicate over shared memory or over 
		// the network
		StationControllerInterface *stationControllerInterface
					= new StationControllerInterface(
								(StationControllerKind)controllerType,
								xmlFiles);

		// Create a new Station Controller object.
		StationController *controller = new StationController(
			(StationControllerKind)controllerType,
			stationControllerInterface);

		// Process incoming lots, including sending lot updates over
		// RTI Connext
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
//   1. Wait for lot status (filtered so it will only receive lots that are 
//      assigned to this station controller, or that have been completed)
//   2. Update lots to say they are being processed
//   2. Process lots
//   3. Update lot status to say it is assigned to the next controller
//
void StationController::ProcessLots()
{
	while (!_shuttingDown)
	{

		// --- Wait for lots to process ---

		string controllerKindString;
		StationControllerType::GetControllerPrettyName(
			_stationControllerKind, controllerKindString);
		cout << "Station controller "
			<< controllerKindString.c_str()
			<< " waiting for data" << endl;

		vector< DdsAutoType<ChocolateLotState> > lotsToProcess;

		// This network interface receives lot state updates that are filtered
		// for just this station controller.  This method will block this 
		// thread until there are lots that should be processed (or a timeout
		// occurs).
		_networkInterface->
			GetChocolateLotStateReader()->WaitForChocolateLotUpdates(
					&lotsToProcess);

		// --- Update lots to WAITING, or unregister completed lots --- 

		// Announce that all lots I have received requests for are waiting at
		// this StationController to be processed.
		for (int i = 0; i < lotsToProcess.size(); i++)
		{
			UpdateState(&lotsToProcess[i]);
		}

		// --- Process lots --- 
		// Process the lots that we know about. "Processing" a lot involves
		// just sleeping in place of real functionality
		for (int i = 0; i < lotsToProcess.size(); i++)
		{
			ProcessLot(&lotsToProcess[i]);
		}

	}
}

// ----------------------------------------------------------------------------
// UpdateState:
void StationController::UpdateState(DdsAutoType<ChocolateLotState> *lotState)
{

	// Copy the lot state that was received into a new object we can modify
	DdsAutoType<ChocolateLotState> updatedState = *lotState;

	// Controller updating/unregistering this lot is me
	updatedState.controller = _stationControllerKind;

	// --- Unregister completed lots ---
	// If this lot is entirely completed being created, I can
	// unregister it - removing any information that I was storing
	// about its state.  This means that late-joining applications will
	// not receive updates about this lot from me. If we fail to
	// unregister, the state of this lot will be available until this
	// application shuts down.
	if (updatedState.lotStatus == LOT_COMPLETED)
	{
		// Call to unregister lot
		_networkInterface->GetChocolateLotStateWriter()->
			UnregisterChocolateLotState(updatedState);
		return;
	}

	// --- Update lots assigned to me to waiting state --- 
	// If this lot is being assigned to me, update its status to say 
	// it is waiting at my station

	// Next station is invalid until I am complete
	updatedState.nextController = INVALID_CONTROLLER;

	// State is waiting at the controller
 	updatedState.lotStatus = WAITING_AT_SC;

	// Write this update to the network
	_networkInterface->GetChocolateLotStateWriter()->
		PublishChocolateLotState(updatedState);
}


// ----------------------------------------------------------------------------
// ProcessLot:
void StationController::ProcessLot(DdsAutoType<ChocolateLotState> *lotState)
{
	// If this lot is completed, don't process it.
	if (lotState->lotStatus == LOT_COMPLETED)
	{
		return;
	}

	// Copy the lot state that was received into a new object we can modify
	DdsAutoType<ChocolateLotState> updatedState = *lotState;

	// I am the current controller, and the current state is I am processing it
	updatedState.controller = _stationControllerKind;
 	updatedState.lotStatus = PROCESSING_AT_SC;

	// No next controller assigned until I am done
	updatedState.nextController = INVALID_CONTROLLER;

	// Write the chocolate lot state over the network
	_networkInterface->GetChocolateLotStateWriter()->
		PublishChocolateLotState(updatedState);

	// --- Query recipe for this lot --- 

	// The GetRecipe() call queries recipes that are stored in the
	// middleware's queue.
	DdsAutoType<ChocolateRecipe> recipe;
	bool haveRecipe = false;
	while (!haveRecipe)
	{
		haveRecipe = 
			_networkInterface->GetRecipeReader()->GetRecipe(
				lotState->recipeName, &recipe);
		if (!haveRecipe)
		{ 
			DDS_Duration_t recipeWait;
			// 10 ms
			recipeWait.sec = 10;
			recipeWait.nanosec = 0;

			cout << "Have not received the required recipe.  Waiting for " <<
				recipeWait.sec << " seconds for recipe." << 
				endl;
				NDDSUtility::sleep(recipeWait);
		}
	}

	// Get the current recipe step information to know how to
	// process the lot
	RecipeStep currentStep;

	// Start to fill in the next state of the chocolate lot based
	// on the next recipe step.
	DdsAutoType<ChocolateLotState> nextState
		= *lotState;

	// Iterate over the recipe steps 
	for (int j = 0; j < recipe.steps.length(); j++)
	{
		// Iterate over the recipe until reaching the current step
		// in the process.
		if (recipe.steps[j].stationController == _stationControllerKind)
		{
			// Set currentStep to the current recipe step
			currentStep = recipe.steps[j];

			// If this is the last step in the recipe, we can mark
			// this lot as completed.
			if (j == recipe.steps.length() - 1)
			{
				nextState.nextController = INVALID_CONTROLLER;
				nextState.lotStatus = LOT_COMPLETED;
			} else
			{
				nextState.nextController = 
					recipe.steps[j + 1].stationController;
				nextState.lotStatus = ASSIGNED_TO_SC;
			}

			break;
		}
	}

	// --- "Process" lot (really just sleep) --- 
	DDS_Duration_t busySleep;
	busySleep.sec = currentStep.seconds;
	busySleep.nanosec = 0;

	// --- Print an update --- 
	string controllerKindString;
	StationControllerType::GetControllerPrettyName(
		_stationControllerKind, controllerKindString);
	cout << "Station controller "
		<< controllerKindString.c_str()
		<< " processing lot #" 
		<< updatedState.lotID
		<< " for " 
		<< currentStep.seconds
		<< " seconds" << endl;
	NDDSUtility::sleep(busySleep);
			
	// --- Prepare the next state to publish --- 

	// Add the ingredients from this station controller to the
	// ingredient list in this lot.

	// Increase the length of the ingredients list by 1
	nextState.ingredients.ensure_length(
		nextState.ingredients.length() + 1,
		nextState.ingredients.length() + 1);
	string ingredientName;
					
	// Add the ingredient to the list in the chocolate lot state
	StationControllerType::GetControllerIngredientName(
			_stationControllerKind, ingredientName);
	nextState.ingredients[nextState.ingredients.length() - 1] =
		new char [ingredientName.size() + 1];
	strcpy(nextState.ingredients[nextState.ingredients.length() - 1],
		const_cast<char *>(ingredientName.c_str()));

	// Fill in the next controller based on the recipe we queried
	// earlier
	string nextControllerKindString;
	StationControllerType::GetControllerPrettyName(
		nextState.nextController, nextControllerKindString);
	cout << "Station controller "
		<< controllerKindString.c_str()
		<< " sending lot #" 
		<< nextState.lotID 
		<< " to " 
		<< nextControllerKindString.c_str() << endl; 

	// --- Publish updated state --- 
	// Update to say we are done with lot, and it is time for
	// the next station controller to process it, or that it is 
	// completed.
	_networkInterface->GetChocolateLotStateWriter()->
		PublishChocolateLotState(nextState);

}

// ----------------------------------------------------------------------------
// PrintHelp:
// Function that prints out the help if somebody runs the application with 
// --help
//
void PrintHelp()
{
	cout << "Valid options are: " << endl;
	cout << 
		"    --controller-type [number]" <<
		" Valid values 1-5. Type of controller this app "
		<< endl
		<< "                               " 
		<< "represents" 
		<< endl;
	cout << 
		"    --no-multicast" <<
		"             Do not use multicast " << 
		"(note you must edit XML" << endl <<
		"                               " <<
		"config to include IP addresses)" 
		<< endl;

}
