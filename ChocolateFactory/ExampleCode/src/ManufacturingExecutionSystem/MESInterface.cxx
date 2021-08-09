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

#include "MESInterface.hpp"

using namespace com::chocolatefactory::generated;

// ------------------------------------------------------------------------- //
// The MESInterface is the network interface to the whole Manufacturing
// Execution System application.  This creates DataReaders and DataWriters
// in order to receive and send data.
//
// This interface is built from:
// 1. Network data types and topic names defined in the IDL file
// 2. XML configuration files that describe the QoS profiles that should be
//    used by individual DataWriters and DataReaders.  These describe the
//    movement and persistence characteristics of the data (how reliable should
//    this be?), as well as other QoS such as resource limits.
// 3. The code itself creates DataReaders and DataWriters, and selects which
//    profile to use when creating the DataReaders and DataWriters.
//
// Reading ChocolateLotState data:
// ------------------------------
// The Manufacturing Execution System listens to chocolate lot state data that
// indicates the current location of the chocolate lot state according to each
// Station Controller.
//
// !!!
// NOTE: This may receive updates about a chocolate lot state out of order,
// because the chocolate lot state is being updated by multiple applications
// that could reside on multiple machines.  Getting in-order data from multiple
// sources can be difficult, and may require finely-synchronized clocks on each
// machine.
//
// Writing ChocolateLotState data:
// ----------------------------
// This application sends chocolate lot state data, using the announcement to
// assign the chocolate lot to a particular controller.  This sets the
// chocolate lot state to:
//    - Assigned to the next station controller.
//
// For information on the ChocolateRecipe or ChocolateLotState types, please see
// the ChocolateFactory.idl file.
//
// For information on the quality of service for state data, please see the
// recipe_profiles_multicast.xml file.
//
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

MESInterface::MESInterface(std::vector<std::string>& qosFileNames) :
    _profile(QOS_PROFILE_STATE_DATA),
    _communicator(DDSCommunicator(qosFileNames, _profile))
{
    // Note: all data in this example is "state data."  The string constants
    // with the QoS library name and the QoS profile name are configured as
    // constants in the .idl file.  The profiles themselves are configured in
    // the .xml file. Look in the XML for more details on the definition of
    // state data.

    _topicChocolateLotState = new dds::topic::Topic<ChocolateLotState>(
        _communicator.Participant(), CHOCOLATE_LOT_TOPIC,
        _communicator.Qos().topic_qos(_profile));
    _writerChocolateLotState = new dds::pub::DataWriter<ChocolateLotState>(
        _communicator.Publisher(), *_topicChocolateLotState,
        _communicator.Qos().datawriter_qos(_profile));
    _readerChocolateLotState = new dds::sub::DataReader<ChocolateLotState>(
        _communicator.Subscriber(), *_topicChocolateLotState,
        _communicator.Qos().datareader_qos(_profile));
}

// ------------------------------------------------------------------------- //
// Destruction of objects within this class are handled in the destruction of
// the DDSCommunicator class
MESInterface::~MESInterface()
{ }