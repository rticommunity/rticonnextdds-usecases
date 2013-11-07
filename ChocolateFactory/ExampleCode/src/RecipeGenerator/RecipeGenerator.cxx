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
#include "../Generated/ChocolateFactorySupport.h"
#include "../CommonInfrastructure/DDSTypeWrapper.h"
#include "RecipePublisherInterface.h"

using namespace std;
using namespace com::rti::chocolatefactory::generated;

void PrintHelp();

// ------------------------------------------------------------------------- //
//
// 
// This application creates a number of recipes that are available for, this
// factory, and sends them over the network.  It sends all of these recipes
// immediately using a design for state data.  This means that the recipes
// are available to any interested application as soon as that appliation
// starts up.
//
// The recipe data is modeled as RTI Connext DDS "state data," meaning:
//   1) the recipe is modeled to have a key field which differentiates 
//      individual recipes.  This key field is the recipe name.
//
//   and that it is sent:
//   1) Reliably
//   2) Durably - meaning that this application can send a recipe, and
//      even if the subscribing applications do not exist, yet, they will be
//      notified of all recipes as soon as they create the corresponding
//      DataReader.
//   3) With a history set to: kind = keep last, depth = 1.  This means that 
//      just the most recent update to each recipe will be sent to 
//      DataReaders at startup.  This means that it a recipe is updated, 
//      other applications will see only the updated recipe.
//      Note:  THIS HISTORY SETTING IS NOT APPROPRIATE FOR STRICT RELIABLITY.
//      If you want to see all the updates to a particular recipe that have
//      ever been made, this setting should be changed to history= keep all.
//      The current setting guarantees delivery of the _most recent_ update
//      to the recipe.
//
// ------------------------------------------------------------------------- //

int main(int argc, char *argv[])
{

	bool multicastAvailable = true;
	for (int i = 0; i < argc; i++)
	{

		if (0 == strcmp(argv[i], "--no-multicast"))
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
	int recipeNum = 3;
	const std::string recipes[] = {
		"Dark","Milk","White"};
	

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
		// actually sends the recipe information over the transport 
		// (shared memory or over the network).  Look into this class to see
		// what you need to do to implement an RTI Connext DDS application that
		// writes data.
		RecipePublisherInterface recipeInterface(xmlFiles);


		DDS_Duration_t send_period = {0,100000000};

		cout << "Sending recipes over RTI Connext DDS" << endl;


		// Write all recipes up to the number specified
		for (int i = 0; i < recipeNum; i++) 
		{

			// Allocate a recipe structure
			DdsAutoType<ChocolateRecipe> recipe;

			// Print each of the three recipes
			sprintf(recipe.recipeName, "%s", 
				recipes[i].c_str()); 

			// This sets up the recipes that can be used to create dark 
			// chocolate, milk chocolate, or white chocolate.  In place of real
			// recipe steps, it includes the timing that each step in the 
			// recipe should require.  
			if (0 == strcmp(recipe.recipeName, "Dark"))
			{
				recipe.steps.ensure_length(4,4);
				recipe.steps[0].stationController = SUGAR_CONTROLLER;
				recipe.steps[0].seconds = 1;
				recipe.steps[1].stationController = COCOA_BUTTER_CONTROLLER;
				recipe.steps[1].seconds = 2;
				recipe.steps[2].stationController = COCOA_LIQUOR_CONTROLLER;
				recipe.steps[2].seconds = 3;
				recipe.steps[3].stationController = VANILLA_CONTROLLER;
				recipe.steps[3].seconds = 4;
			}
			if (0 == strcmp(recipe.recipeName, "Milk"))
			{
				recipe.steps.ensure_length(5,5);
				recipe.steps[0].stationController = SUGAR_CONTROLLER;
				recipe.steps[0].seconds = 1;
				recipe.steps[1].stationController = COCOA_BUTTER_CONTROLLER;
				recipe.steps[1].seconds = 2;
				recipe.steps[2].stationController = COCOA_LIQUOR_CONTROLLER;
				recipe.steps[2].seconds = 3;
				recipe.steps[3].stationController = MILK_CONTROLLER;
				recipe.steps[3].seconds = 4;
				recipe.steps[4].stationController = VANILLA_CONTROLLER;
				recipe.steps[4].seconds = 5;
			}
			if (0 == strcmp(recipe.recipeName, "White"))
			{
				recipe.steps.ensure_length(4,4);
				recipe.steps[0].stationController = SUGAR_CONTROLLER;
				recipe.steps[0].seconds = 1;
				recipe.steps[1].stationController = COCOA_BUTTER_CONTROLLER;
				recipe.steps[1].seconds = 2;
				recipe.steps[2].stationController = MILK_CONTROLLER;
				recipe.steps[2].seconds = 3;
				recipe.steps[3].stationController = VANILLA_CONTROLLER;
				recipe.steps[3].seconds = 4;

			}


			// Write the data to the network.  This is a thin wrapper 
			// around the RTI Connext DDS DataWriter that writes data to
			// the network.
			recipeInterface.Write(recipe);

			// Sleep before sending the next recipe.  There is no real
			// requirement to sleep between sends, except that it stresses
			// the network less
			NDDSUtility::sleep(send_period);
		}

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

void PrintHelp()
{
	cout << "Valid options are: " << endl;
	cout << 
		"    --no-multicast" <<
		"                 Do not use multicast " << 
		"(note you must edit XML" << endl <<
		"                                   " <<
		"config to include IP addresses)" 
		<< endl;

}
