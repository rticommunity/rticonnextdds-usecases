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

#ifndef CHOCOLATE_LOT_STATE_ENTITIES_H
#define CHOCOLATE_LOT_STATE_ENTITIES_H

#include <dds/dds.hpp>
#include "DDSCommunicator.hpp"
#include "../Generated/ChocolateFactory.hpp"

using namespace com::chocolatefactory::generated;

// ------------------------------------------------------------------------- //
//
// ChocolateLotStateCommon:
// Used for dealing with the chocolate lot state. This encapsulates the topic
// used for DataReaders and DataWriters of the state data.
//
// ------------------------------------------------------------------------- //
class ChocolateLotStateCommon {
protected:
    // --- Constructors ---
    // Default constructor that creates the topic from the default profile
    // provided by the DDSCommunicator object
    ChocolateLotStateCommon(DDSCommunicator& comm);
    // Constructor that creates the topic from the specified profile
    ChocolateLotStateCommon(DDSCommunicator& comm, const std::string& profile);

    // --- Accessors ---
    // Accessor for the topic data created in initialization
    const dds::topic::Topic<ChocolateLotState>& Topic();

private:
    dds::topic::Topic<ChocolateLotState>& _topic;
};

// ------------------------------------------------------------------------- //
//
// ChocolateLotStateReader:
// Used for receiving the chocolate lot state.  This encapsulates the concepts
// of a DDS type-specific DataReader (for type ChocolateLotState), along with
// the mechanisms for accessing data - in this case, this allows the
// application to block one of its threads to wait for data from the
// ChocolateLotStateReader.
//
// ------------------------------------------------------------------------- //
class ChocolateLotStateReader : ChocolateLotStateCommon {
public:
    // --- Constructor ---
    // This creates a DDS DataReader that subscribes to chocolate lot
    // information. This uses the app object to access the DomainParticipant,
    // and it uses the QoS profiles specified when creating the DataReader.  The
    // XML QoS files were previously configured when the
    // StationControllerInterface's DDSCommunicator was created.
    ChocolateLotStateReader(DDSCommunicator& comm, const std::string& profile,
        const StationControllerKind kind);

    // --- Destructor ---
    ~ChocolateLotStateReader();

    const dds::sub::DataReader<ChocolateLotState>& Reader();

private:
    // --- Private methods ---

    // Create reader
    dds::sub::DataReader<ChocolateLotState>& CreateReader(DDSCommunicator& comm,
        const std::string& profile, const StationControllerKind kind);
    
    // --- Private members ---

    // Application-specific DDS DataReader for receiving chocolate lot state
    // data
    dds::sub::DataReader<ChocolateLotState>& _reader;
};

// ------------------------------------------------------------------------- //
//
// ChocolateLotStateWriter:
// This class is used to create a write chocolate lot data over the network.
//
class ChocolateLotStateWriter : ChocolateLotStateCommon {
public:
    // --- Constructor ---
    // This creates a DDS DataWriter that publishes the chocolate lot state
    ChocolateLotStateWriter(DDSCommunicator& comm, const std::string& profile);

    // --- Destructor ---
    ~ChocolateLotStateWriter();

    // --- Sends the Chocolate Lot State ---
    // Uses DDS interface to send a chocolate lot state update over the network
    // or shared memory to interested applications subscribing to chocolate
    // lot state information.
    void PublishChocolateLotState(const ChocolateLotState& lotState);

    // --- Unregisters the lot state ---
    // When this application sees that the chocolate lot is finished, it
    // unregisters the lot state
    void UnregisterChocolateLotState(const ChocolateLotState& lotState);

private:
    dds::pub::DataWriter<ChocolateLotState>& CreateWriter(
        DDSCommunicator& comm, const std::string& profile);

    // --- Private members ---

    // The application-specific DDS DataWriter that sends chocolate lot state
    // updates over the network or shared memory
    dds::pub::DataWriter<ChocolateLotState>& _writer;
};

#endif