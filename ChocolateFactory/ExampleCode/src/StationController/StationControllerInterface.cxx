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

#include <vector>
#include <sstream>
#include <iostream>
#include "../Generated/ChocolateFactory.hpp"
#include "../CommonInfrastructure/EnumPrintHelpers.hpp"
#include "StationControllerInterface.hpp"

using namespace std;
using namespace com::chocolatefactory::generated;
using namespace dds::topic;
using namespace dds::pub;
using namespace dds::sub;

// ------------------------------------------------------------------------- //
// The StationControllerInterface is the network interface to the whole
// Station Controller application.  This creates DataReaders and DataWriters
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

StationControllerInterface::StationControllerInterface(StationControllerKind id,
    vector<string> qosFileNames, string lotStateQosProfile, 
    string recipeQosProfile) : 
    _comm(DDSCommunicator(qosFileNames, (QOS_LIBRARY + "::" + 
        QOS_PROFILE_STATE_DATA)))    
{
    _stationControllerID = id;

    // All data in this example is "state data."  The string constants with the
    // QoS library name and the QoS profile name are configured as constants in
    // the .idl file.  The profiles themselves are configured in the .xml file.
    // Look in the XML for more details on the definition of state data.

    _topicChocolateLotState = new Topic<ChocolateLotState>(_comm.Participant(),
        CHOCOLATE_LOT_TOPIC, _comm.Qos().topic_qos(lotStateQosProfile));
    _cftChocolateLotState = new ContentFilteredTopic<ChocolateLotState>(
        *_topicChocolateLotState, "ContentFilter", Filter(
            "lotStatus = 'LOT_COMPLETED' OR nextController = %0", {
                StationControllerType::ControllerEnumName(id)
            })
        );
    _topicChocolateRecipe = new Topic<ChocolateRecipe>(_comm.Participant(),
        RECIPE_TOPIC, _comm.Qos().topic_qos(recipeQosProfile));
    _writerChocolateLotState = new DataWriter<ChocolateLotState>(_comm.Publisher(),
        *_topicChocolateLotState, _comm.Qos().datawriter_qos(lotStateQosProfile));
    _readerChocolateLotState = new DataReader<ChocolateLotState>(_comm.Subscriber(),
        *_cftChocolateLotState, _comm.Qos().datareader_qos(lotStateQosProfile));
    _readerRecipe = new DataReader<ChocolateRecipe>(_comm.Subscriber(),
        *_topicChocolateRecipe, _comm.Qos().datareader_qos(recipeQosProfile));
}

// ------------------------------------------------------------------------- //
// Deleting the ChocolateLotState DataWriter, the ChocolateLotState DataReader,
// the ChocolateRecipeDataReader, and the communicator infrastructure.  See the
// individual destructors to see how these are deleted.
StationControllerInterface::~StationControllerInterface()
{ }

ChocolateRecipe StationControllerInterface::GetRecipe(const string recipeName)
{
    // Create a placeholder with only the key field filled in.  This will be
    // used to retrieve the recipe instance (if it exists).
    for (auto sample : _readerRecipe->read()) {
        if (recipeName == sample.data().recipeName())
            return sample.data();
    }
}
