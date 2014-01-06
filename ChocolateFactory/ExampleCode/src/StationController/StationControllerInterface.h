/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#ifndef STATION_CONTROLLER_INTERFACE_H
#define STATION_CONTROLLER_INTERFACE_H


#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "../CommonInfrastructure/DDSTypeWrapper.h"
#include "../CommonInfrastructure/ChocolateLotStateEntities.h"
#include "../Generated/ChocolateFactory.h"
#include "../Generated/ChocolateFactorySupport.h"

#include <map>


// ----------------------------------------------------------------------------
// A station controller is responsible for:
//   1. Listing for chocolate lot state data that indicates it should be 
//      responsible for the next step in a chocolate recipe for a given lot.
//   2. Updating the chocolate lot state to indicate that it is processing a
//      lot, or to send the chocolate lot to the next station controller.
//
// The station controller interface is composed of two parts:  
//
// Reading ChocolateLotState data:
// ------------------------------
// The station controller listens to chocolate lot state data that indicates 
// that a chocolate lot is on the way to this station controller.
//
// It uses a DDS DataReader, with a content filter to receive only updates
// that indicate that it is the next station controller to process the lot.
// 
// Writing ChocolateLotState data:
// ----------------------------
// This application sends chocolate lot state data, announcing that the current
// lot of chocolates is either:
//   1. Waiting to be processed by this station controller
//   2. Being processed by this station controller
//   3. Done being processed by this station controller/ready to be processed
//      by the next station controller.
// 
// For information on the ChocolateRecipe or ChocolateLotState types, please see 
// the ChocolateFactory.idl file.  
//
// For information on the quality of service for state data, please see the 
// recipe_profiles_multicast.xml file.
//
// Reading Recipe data:
// --------------------
// This application reads recipe data to know which state controller to send
// the chocolate lot to when it is done.
//
// Quality of Service:
// -------------------
// All of the data in this example is modeled as "state data," which means that:
//   1. It is sent reliably (RELIABLE_RELIABILITY_QOS)
//   2. It is made available to late-joining applications as soon as they start
//      (TRANSIENT_LOCAL_DURABILITY_QOS)
//   3. A predetermined amount of state is sent to any late-joiners.  In this 
//      case, applications are only interested in the current state of each
//      chocolate lot (or the current chocolate recipe), which translates to a
//      history with depth = 1, kind = KEEP_LAST_HISTORY_QOS
//

class ChocolateLotStateWriter;
class ChocolateLotStateReader;
class ChocolateRecipeReader;


// ------------------------------------------------------------------------- //
//
// StationControllerInterface:
// A class that sets up the DDS interface (the network interface) of this 
// chocolate factory's station controller applications.
//
// This includes creating appropriate DDS DataWriters, DDS DataReaders, and 
// all other DDS objects.
//
// ------------------------------------------------------------------------- //
class StationControllerInterface
{

public:

	// This takes in the ID of the station controller, 

	// The station controller ID is used both when updating the chocolate lot
	// state, and when listening for a chocolate lot state.  

	// When listening for the chocolate lot state, this either:
	// 1. Installs a content filtered topic to listen only for lots that
	//    are assigned to it, or
	// 2. Installs a normal topic and monitors all updates to the chocolate 
	//    lot state.


	// --- Constructor --- 
	StationControllerInterface(
		com::rti::chocolatefactory::generated::StationControllerKind 
				stationControllerID, 
		std::vector<std::string>qosFileNames);

	// --- Destructor --- 
	virtual ~StationControllerInterface();

	// --- Getter for the ChocolateLotStateWriter --- 
	// This returns a ChocolateLotStateWriter object, which is the part of the 
	// network interface that sends the chocolate lot's current state data over
	// the network.  Look at the ChocolateLotStateWriter class to see how to write
	// data in RTI Connext DDS.
	ChocolateLotStateWriter *GetChocolateLotStateWriter() 
	{
		return _chocolateLotStateWriter;
	}

	// --- Getter for the ChocolateLotStateReader --- 
	// This returns the ChocolateLotState reader - a small wrapper around the 
	// ChocolateLotStateReader that initializes the reader, the content filtered
	// topic, and uses the DDS "WaitSet" object to wait for the chocolate lot 
	// state updates
	ChocolateLotStateReader *GetChocolateLotStateReader() 
	{
		return _chocolateLotStateReader;
	}

	// --- Getter for the RecipeReader --- 
	// This returns the Chocolate recipe reader - a small wrapper around the 
	// ChocolateRecipeDataReader that initializes the reader and uses the 
	// DDS "WaitSet" object to wait for recipes
	ChocolateRecipeReader *GetRecipeReader() 
	{
		return _recipeReader;
	}


	// --- Getter for Communicator --- 
	// Accessor for the communicator (the class that sets up the basic
	// DDS infrastructure like the DomainParticipant).
	// This allows access to the DDS DomainParticipant/Publisher/Subscriber
	// classes
	DDSCommunicator *GetCommunicator() 
	{
		return _communicator; 
	}

	// --- Getter for Controller ID --- 
	// Accessor for the controller ID
	const com::rti::chocolatefactory::generated::StationControllerKind 
		GetStationControllerID() 
	{
		return _stationControllerID; 
	}

private:
	// --- Private members ---

	// This contains the calls that allow the interface to create a 
	// "DomainParticipant", the first object that must be created to 
	// communicate over a DDS middleware.
	DDSCommunicator *_communicator;

	// If this is a controller, this filed is used to identify which station 
	// controller this is, and what part of the recipe it is responsible for.
	// If this is not a station controller, this is set to invalid
	com::rti::chocolatefactory::generated::StationControllerKind 
		_stationControllerID;

	// Wrapper class around RTI Connext DDS for writing chocolate lot state
	ChocolateLotStateWriter *_chocolateLotStateWriter;

	// Used for receiving chocolate lot state data, and being notified about 
	// the arrival of chocolate lot updates that are specific to this control 
	// station.
	ChocolateLotStateReader *_chocolateLotStateReader;

	// Used for receiving recipe data, and for looking up received recipes.
	ChocolateRecipeReader *_recipeReader;

};



// ------------------------------------------------------------------------- //
//
// ChocolateRecipeReader:
// Used for receiving the chocolate recipes.  This encapsulates the concepts of
// a DDS type-specific DataReader (for type ChocolateRecipe), along with the 
// mechanisms for accessing data - in this case, this allows the application 
// to block one of its threads to wait for data from the ChocolateRecipeReader.
//
// ------------------------------------------------------------------------- //
class ChocolateRecipeReader 
{

public:

	// --- Constructor --- 
	// This creates a DDS DataReader that subscribes to recipe information.  
	// This uses the _communicator object to access the DomainParticipant, and
	// it uses the QoS profiles specified when creating the DataReader.  The 
	// XML QoS fileswere previously configured when the  
	// StationControllerInterface's DDSCommunicator was created.
	ChocolateRecipeReader(StationControllerInterface *comm, 
		DDS::Subscriber *sub, 
		const std::string &qosLibrary, 
		const std::string &qosProfile);


	// --- Destructor --- 
	~ChocolateRecipeReader();

	// --- Retrieve recipes --- 
	// This example receives all recipes, and leaves them in the middleware's
	// queue.  It queries for a particular recipe when it receives an update
	// about a lot and it needs to check the recipe for that lot.
	bool GetRecipe(
		std::string recipeName,
		DdsAutoType<com::rti::chocolatefactory::generated::ChocolateRecipe>
			*recipe);


private:
	// --- Private methods --- 


	// --- Private members ---

	// Contains all the components needed to create the DataReader
	StationControllerInterface *_communicator;

	// Application-specific DDS DataReader for receiving recipe data
	com::rti::chocolatefactory::generated::ChocolateRecipeDataReader *_reader;

};




#endif
