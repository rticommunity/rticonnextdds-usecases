/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.
RTI grants Licensee a license to use, modify, compile, and create derivative
works of the Software.  Licensee has the right to distribute object form only
for use with RTI products.  The Software is provided “as is”, with no warranty
of any type, including any warranty for fitness for any purpose. RTI is under no
obligation to maintain or support the Software.  RTI shall not be liable for any
incidental or consequential damages arising out of the use or inability to use
the software.
**********************************************************************************************/

#ifndef MES_INTERFACE_H
#define MES_INTERFACE_H

#include <sstream>
#include "../Generated/ChocolateFactory.hpp"
#include "../CommonInfrastructure/DDSCommunicator.hpp"

using namespace com::chocolatefactory::generated;

// ----------------------------------------------------------------------------
//
// The manufacturing execution system interface provides lot plans
// over the network (or shared memory) to other applications that are interested
// in monitoring the state of chocolate lots.
//
// Writing chocolate lot state data:
// ---------------------------------
// This application sends chocolate lot state data, configured to behave as
// state data (or last-value cache).  This will reliably deliver each chocolate
// lot state update to both existing and late-joining applications that
// subscribe to chocolate lot state data.
//
// This application is responsible for sending the initial chocolate lot state
// update to announce that there is a new lot that needs to be processed by all
// of the controllers.
//
// For information on the chocolate lot state data type, please see the
// ChocolateFactory.idl file.
//
// For information on the quality of service for chocolate lot state data,
// please see the recipe_profiles_multicast.xml or
// recipe_profiles_no_multicast.xml file.
//
// ----------------------------------------------------------------------------
class MESInterface {
public:
    // --- Constructor ---
    // Initializes the manufacturing executive interface, including creating a
    // DomainParticipant, creating all publishers and subscribers, topics
    // writers and readers.  Takes as input a vector of xml QoS files that
    // should be loaded to find QoS profiles and libraries.
    MESInterface(std::vector<std::string>& xmlFiles);

    // --- Destructor ---
    ~MESInterface();

    // --- Getter for the ChocolateLotStateWriter ---
    // This returns a ChocolateLotStateWriter object, which is the part of the
    // network interface that sends the chocolate lot's current state data over
    // the network.
    dds::pub::DataWriter<ChocolateLotState>& WriterChocolateLotState()
    {
        return _writerChocolateLotState;
    }

    // --- Getter for the ChocolateLotStateReader ---
    // This returns the ChocolateLotState reader - a small wrapper around the
    // ChocolateLotStateDataReader that initializes the reader, the
    // topic, and uses the DDS "WaitSet" object to wait for the chocolate lot
    // state updates
    dds::sub::DataReader<ChocolateLotState>& ReaderChocolateLotState()
    {
        return _readerChocolateLotState;
    }

private:
    // --- Private members ---

    // Stores profile based on elements from IDL file
    std::string _profile;

    // This contains the calls that allow the interface to create a
    // "DomainParticipant", the first object that must be created to
    // communicate over a DDS middleware.
    DDSCommunicator& _communicator;

    // Topic object used to define the datatype use by the ChocolateLotState
    // DataReader and DataWriter
    dds::topic::Topic<ChocolateLotState>& _topicChocolateLotState;

    // DataWriter object for ChocolateLotState
    dds::pub::DataWriter<ChocolateLotState>& _writerChocolateLotState;

    // DataReader used for receiving chocolate lot state data
    dds::sub::DataReader<ChocolateLotState>& _readerChocolateLotState;
};

#endif