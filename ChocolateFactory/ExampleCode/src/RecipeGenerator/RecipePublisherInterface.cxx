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

#include "RecipePublisherInterface.hpp"

using namespace com::chocolatefactory::generated;

// ----------------------------------------------------------------------------
// The RecipePublisherInterface is the network interface to the whole
// application.  This creates a DataWriter in order to send recipe data
// over the network (or shared memory) to other applications that are
// interested in recipes.
//
// This interface is built from:
// 1. Network data types and topic names defined in the IDL file
// 2. XML configuration files that describe the QoS profiles that should be
//    used by individual DataWriters and DataReaders.  These describe the
//    movement and persistence characteristics of the data (how reliable should
//    this be?), as well as other QoS such as resource limits.
// 3. The code itself creates DataWriters, and selects which QoS profile to use
//    when creating the DataWriters.
//
// Writing recipe data:
// --------------------
// This application sends recipes, configured to act as state data
// (or last-value cache).  This will reliably deliver the recipes to both
// existing and late-joining applications that subscribe to recipes.
//
// For information on the recipe data type, please see the
// ChocolateFactory.idl file.
//
// For information on the quality of service for recipe state data, please
// see the recipe_profiles_multicast.xml or recipe_profiles_no_multicast.xml
// file.
// ------------------------------------------------------------------------- //

RecipePublisherInterface::RecipePublisherInterface(
        std::vector<std::string>& xmlFiles) :
    _communicator(DDSCommunicator(xmlFiles))
{
    // Note: all data in this example is "state data."  The string constants
    // with the QoS library name and the QoS profile name are configured as
    // constants in the .idl file.  The profiles themselves are configured in
    // the .xml file. Look in the XML for more details on the definition of
    // state data.

    _topic = new dds::topic::Topic<ChocolateRecipe>(_communicator.Participant(),
        RECIPE_TOPIC, _communicator.Qos().topic_qos());
    _writer = new dds::pub::DataWriter<ChocolateRecipe>(_communicator.Publisher(),
        *_topic, _communicator.Qos().datawriter_qos());
}

// ----------------------------------------------------------------------------
// Destructor.
// Deletes the DataWriter, and the Communicator object
RecipePublisherInterface::~RecipePublisherInterface()
{ }


// ----------------------------------------------------------------------------
// Sends the recipe over a transport (such as shared memory or UDPv4)
// This writes the Recipe data using RTI Connext DDS to any DataReader
// that shares the same Topic
void RecipePublisherInterface::Write(ChocolateRecipe data)
{
    // This actually sends the recipe data over the network.

    // The handle that the write() call takes is a handle to the individual
    // recipe instance - a unique recipe described by a
    // unique recipe name

    // The recipe data has a very simple ID, and does not need high-
    // throughput, so we are not bothering to pre-register the instance
    // handle.  If we did pre-register the instance handle, this could
    // potentially speed up the writing.
    _writer->write(data);

}
