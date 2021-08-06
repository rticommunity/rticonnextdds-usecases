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
#include "ChocolateLotStateEntities.hpp"
#include "EnumPrintHelpers.hpp"

using namespace com::chocolatefactory::generated;
using namespace dds::topic;
using namespace dds::pub;
using namespace dds::sub;

// ------------------------------------------------------------------------- //
// Constructors for the ChocolateLotStateCommon base class. The topic object is
// the description of the data that you will be sending. It associates a
// particular data type with a name that describes the meaning of the data.
// Along with the data types, and whether your application is reading or
// writing particular data, this is the data interface of your application.

// This topic has the name CHOCOLATE_LOT_TOPIC - a constant string that is
// defined in the .idl file. (It is not required that you define your topic
// name in IDL, but it is a best practice for ensuring the data interface of
// an application is all defined in one place.) Generally you can register all
// topics and types up-front if necessary.

// This can be done at any time before creating the DataWriters and
// DataReaders. In some systems, this is done in a separate initialization all
// at once - especially in applications that read and write the same topic.
ChocolateLotStateCommon::ChocolateLotStateCommon(DDSCommunicator& comm) :
    _topic(dds::topic::Topic<ChocolateLotState>(comm.Participant(), CHOCOLATE_LOT_TOPIC))
{}
ChocolateLotStateCommon::ChocolateLotStateCommon(DDSCommunicator& comm,
    const std::string& profile) :
    _topic(dds::topic::Topic<ChocolateLotState>(comm.Participant(),
        CHOCOLATE_LOT_TOPIC, comm.Qos().topic_qos(profile)))
{}

// Accessor for the private Topic data
const dds::topic::Topic<ChocolateLotState>& ChocolateLotStateCommon::Topic()
{
    return _topic;
}

// ------------------------------------------------------------------------- //
// Create the ChocolateLotState DataWriter.  This uses the
// DDSCommunicator's DomainParticipant object to create a
// DataWriter and Topic.
ChocolateLotStateWriter::ChocolateLotStateWriter(DDSCommunicator& comm,
    const std::string& profile) :
    ChocolateLotStateCommon(comm, profile),
    _writer(CreateWriter(comm, profile))
{
}

// ------------------------------------------------------------------------- //
// Destructor for the ChocolateLotStateWriter
ChocolateLotStateWriter::~ChocolateLotStateWriter()
{
}

dds::pub::DataWriter<ChocolateLotState>& ChocolateLotStateWriter::CreateWriter(
    DDSCommunicator& comm, const std::string& profile)
{
    // Create a DataWriter The topic object is the description of the data that
    // you will be sending. It associates a particular data type with a name
    // that describes the meaning of the data. Along with the data types, and
    // whether your application is reading or writing particular data, this is
    // the data interface of your application.

    // This topic has the name CHOCOLATE_LOT_TOPIC - a constant string that was
    // defined in the .idl file. (It is not required that you define your topic
    // name in IDL, but it is a best practice for ensuring the data interface of
    // an application is all defined in one place. Generally you can register
    // all topics and types up-front if necessary.

    // Use QoS loaded from the XML file

    // Create the DDS DataWriter object that sends data over the network (or
    // shared memory)

    auto writer = rti::pub::find_datawriter_by_topic_name
        <DataWriter<ChocolateLotState>>(comm.Publisher(), CHOCOLATE_LOT_TOPIC);

    if (writer == dds::core::null)
        return DataWriter<ChocolateLotState>(
            comm.Publisher(), Topic(), comm.Qos().datawriter_qos(profile));
    else
        return writer;
}

// ------------------------------------------------------------------------- //
// Write the data into the DDS "cloud" - in other words, write the data,
// within the numbered domain that the DomainParticipant was created with,
// to whichever DataReaders of the same topic were discovered over the
// available transports.
void ChocolateLotStateWriter::PublishChocolateLotState(const ChocolateLotState& lotState)
{
    _writer.write(lotState);
}

// ------------------------------------------------------------------------- //
// Unregisters the lot state published by this station controller.  This says
// that this station controller no longer wants to provide an update to the
// state of a particular lot.
// (The application calls this when a lot has completed all stages of
// processing so there is no need for a station controller to continue to
// provide its processing state for that lot).
void ChocolateLotStateWriter::UnregisterChocolateLotState(const ChocolateLotState& lotState)
{
    auto handle = dds::core::InstanceHandle::nil();

    // Retrieve the handle of the instance we were disposing
    handle = _writer.lookup_instance(lotState);

    // Note that DDS has two ways to indicate that an instance has gone away
    // it can unregister the instance or dispose it.  Also, by default when
    // the DataWriter unregisters an instance, it also disposes it.  If you
    // dispose and instance, the memory for the instance is not cleaned up,
    // with the expectation that it will be reused.
    // In this case, the next station controller in the factory will start
    // writing the lot state for this lot instance.  We don't want to dispose
    // that lot, but only unregister it.
    _writer.unregister_instance(handle);
}

// ------------------------------------------------------------------------- //
// This creates the DDS DataReader that receives updates about chocolate lots.
ChocolateLotStateReader::ChocolateLotStateReader(DDSCommunicator& comm,
    const std::string& profile, const StationControllerKind kind) :
    ChocolateLotStateCommon(comm, profile),
    _reader(CreateReader(comm, profile, kind))
{ }

// ------------------------------------------------------------------------- //
// Destory the chocolate lot DataReader and WaitSet.
ChocolateLotStateReader::~ChocolateLotStateReader()
{ }

// Create the DataReader
//
// If this ChocolateLotStateReader is receiving data for a real station
// controller, it filters data so it receives data only for that controller If
// it is being used by another object such as the MES, it does not filter, so
// all ChocolateLotState updates are received by the DataReader. This DataReader
// will receive the chocolate lot, and will store that data in the middleware's
// queue to be queried by the application Note that if this DataReader belongs
// to a particular StationController type, it will filter to only receive
// updates for that station controller. If it belongs to a non-station
// controller it does not filter.
dds::sub::DataReader<ChocolateLotState>& ChocolateLotStateReader::CreateReader(
    DDSCommunicator& comm, const std::string& profile, const StationControllerKind kind)
{
    // Get the QoS profile from the QoS Provider
    auto qos = comm.Qos().datareader_qos(profile);

    if (kind != StationControllerKind::INVALID_CONTROLLER) {
        // Static helper method that converts an enumeration into the string
        // that represents that enumeration
        std::vector<std::string> parameters = { StationControllerType::ControllerEnumName(kind) };

        // Filter to receive updates if: 1) This is assigned to me or 2) this
        // lot is in state LOT_COMPLETED (at which point I unregister the
        // instance) Note: The _parameters StringSeq will delete this
        // char * when the ChocolateLotStateReader class is deleted, so must
        // duplicate the string using DDS::String_dup.
        auto cft = ContentFilteredTopic<ChocolateLotState>
            (Topic(), "ContentFilter",
                Filter("lotStatus = 'LOT_COMPLETED' OR nextController = %0", parameters));

        return DataReader<ChocolateLotState>(comm.Subscriber(), cft, qos);
    }
    else {
        return DataReader<ChocolateLotState>(comm.Subscriber(), Topic(), qos);
    }
}

const dds::sub::DataReader<ChocolateLotState>& ChocolateLotStateReader::Reader()
{
    return _reader;
}