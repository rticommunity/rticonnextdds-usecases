/*
 * (c) 2021 Copyright, Real-Time Innovations, Inc. (RTI) All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the software solely for use with RTI Connext DDS.  Licensee may
 * redistribute copies of the software provided that all such copies are
 * subject to this license. The software is provided "as is", with no warranty
 * of any type, including any warranty for fitness for any purpose. RTI is
 * under no obligation to maintain or support the software.  RTI shall not be
 * liable for any incidental or consequential damages arising out of the use or
 * inability to use the software.
 */
#ifndef STATION_CONTROLLER_INTERFACE_H
#define STATION_CONTROLLER_INTERFACE_H

#include <map>
#include "dds/dds.hpp"
#include "../CommonInfrastructure/DDSCommunicator.hpp"
#include "../Generated/ChocolateFactory.hpp"

using namespace std;
using namespace com::chocolatefactory::generated;

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
class StationControllerInterface {
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
    StationControllerInterface(StationControllerKind stationControllerID,
        vector<string> qosFileNames, string lotStateQosProfile,
        string recipeQosProfile);

    // --- Destructor ---
    virtual ~StationControllerInterface();

    // --- Getter for the ChocolateLotStateWriter ---
    // This returns a ChocolateLotStateWriter object, which is the part of the
    // network interface that sends the chocolate lot's current state data over
    // the network.  Look at the ChocolateLotStateWriter class to see how to
    // write data in RTI Connext DDS.
    dds::pub::DataWriter<ChocolateLotState>& WriterChocolateLotState()
    {
        return _writerChocolateLotState;
    }

    // --- Getter for the ChocolateLotStateReader ---
    // This returns the ChocolateLotState reader - a small wrapper around the
    // ChocolateLotStateReader that initializes the reader, the content filtered
    // topic, and uses the DDS "WaitSet" object to wait for the chocolate lot
    // state updates
    dds::sub::DataReader<ChocolateLotState>& ReaderChocolateLotState()
    {
        return _readerChocolateLotState;
    }

    // --- Getter for the RecipeReader ---
    // This returns the Chocolate recipe reader - a small wrapper around the
    // ChocolateRecipeDataReader that initializes the reader and uses the
    // DDS "WaitSet" object to wait for recipes
    dds::sub::DataReader<ChocolateRecipe>& ReaderRecipe()
    {
        return _readerRecipe;
    }

    // --- Getter for Controller ID ---
    // Accessor for the controller ID
    const StationControllerKind StationControllerID()
    {
        return _stationControllerID;
    }

    // --- Retrieve recipes ---
    // This example receives all recipes, and leaves them in the middleware's
    // queue.  It queries for a particular recipe when it receives an update
    // about a lot and it needs to check the recipe for that lot.
    ChocolateRecipe GetRecipe(const string recipeName);

private:
    // --- Private members ---

    // This contains the calls that allow the interface to create a
    // "DomainParticipant", the first object that must be created to
    // communicate over a DDS middleware.
    DDSCommunicator& _comm;

    // If this is a controller, this filed is used to identify which station
    // controller this is, and what part of the recipe it is responsible for.
    // If this is not a station controller, this is set to invalid
    StationControllerKind _stationControllerID;

    // Topic object used to define the datatype use by the ChocolateLotState
    // DataWriter
    dds::topic::Topic<ChocolateLotState>& _topicChocolateLotState;
    // Topic object used to define the datatype use by the ChocolateLotState
    // DataReader
    dds::topic::ContentFilteredTopic<ChocolateLotState>& _cftChocolateLotState;
    // Topic object used for Chocolate Recipe reader
    dds::topic::Topic<ChocolateRecipe>& _topicChocolateRecipe;

    // DataWriter object for ChocolateLotState
    dds::pub::DataWriter<ChocolateLotState>& _writerChocolateLotState;

    // DataReader used for receiving chocolate lot state data
    dds::sub::DataReader<ChocolateLotState>& _readerChocolateLotState;

    // Used for receiving recipe data, and for looking up received recipes.
    dds::sub::DataReader<ChocolateRecipe>& _readerRecipe;
};

#endif
