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

#ifndef RECIPE_PUBLISHER_INTERFACE_H
#define RECIPE_PUBLISHER_INTERFACE_H

#include <sstream>
#include "../CommonInfrastructure/DDSCommunicator.hpp"
#include "../Generated/ChocolateFactory.hpp"

using namespace com::chocolatefactory::generated;
using namespace std;

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
class RecipePublisherInterface {
public:
    // --- Constructor ---
    // Initializes the recipe publisher interface, including creating a
    // DomainParticipant, creating all publishers and subscribers, topics
    // writers and readers.  Takes as input a vector of xml QoS files that
    // should be loaded to find QoS profiles and libraries.
    RecipePublisherInterface(vector<string>& xmlFiles);

    // --- Destructor ---
    ~RecipePublisherInterface();

    // --- Sends the recipe ---
    // Uses DDS interface to send a recipe efficiently over the network
    // or shared memory to interested applications subscribing to recipe
    // information.
    void Write(ChocolateRecipe& data);


private:
    // --- Private members ---

    // Used to create basic DDS entities that all applications need
    const DDSCommunicator& communicator_;

    // Recipe publisher specific to this application
    dds::pub::DataWriter<ChocolateRecipe>* writer_;
};

#endif