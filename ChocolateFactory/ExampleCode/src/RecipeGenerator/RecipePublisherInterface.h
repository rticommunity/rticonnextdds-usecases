/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#ifndef RECIPE_PUBLISHER_INTERFACE_H
#define RECIPE_PUBLISHER_INTERFACE_H

#include <sstream>
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "../CommonInfrastructure/DDSTypeWrapper.h"
#include "../Generated/ChocolateFactory.h"
#include "../Generated/ChocolateFactorySupport.h"


// ----------------------------------------------------------------------------
//
// The recipe publisher interface provides recipe data over the network 
// (or shared memory) to other applications that are interested in recipes.
//
// Writing recipe data:
// --------------------
// This application sends recipe data, configured to behave as state data
// (or last-value cache).  This will reliably deliver each recipe to both
// existing and late-joining applications that subscribe to recipes.
//
// For information on the recipe data type, please see the 
// ChocolateFactory.idl file.  
//
// For information on the quality of service for recipe state data, please
// see the recipe_profiles_multicast.xml or recipe_profiles_no_multicast.xml 
// file.
//
// ----------------------------------------------------------------------------
class RecipePublisherInterface
{

public:

	// --- Constructor --- 
	// Initializes the recipe publisher interface, including creating a 
	// DomainParticipant, creating all publishers and subscribers, topics 
	// writers and readers.  Takes as input a vector of xml QoS files that
	// should be loaded to find QoS profiles and libraries.
	RecipePublisherInterface(std::vector<std::string> xmlFiles);

	// --- Destructor --- 
	~RecipePublisherInterface();

	// --- Getter for Communicator --- 
	// Accessor for the communicator (the class that sets up the basic
	// DDS infrastructure like the DomainParticipant).
	// This allows access to the DDS DomainParticipant/Publisher/Subscriber
	// classes
	DDSCommunicator *GetCommunicator() 
	{ 
		return _communicator; 
	}

	// --- Sends the recipe ---
	// Uses DDS interface to send a recipe efficiently over the network
	// or shared memory to interested applications subscribing to recipe
	// information.
	bool Write(DdsAutoType<com::rti::chocolatefactory::generated::ChocolateRecipe> data);


private:
	// --- Private members ---

	// Used to create basic DDS entities that all applications need
	DDSCommunicator *_communicator;

	// Recipe publisher specific to this application
	com::rti::chocolatefactory::generated::ChocolateRecipeDataWriter *_writer;
};

#endif