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

/* DDSCommunicator.cxx

   Defines common DDS communication elements that are to be inherited by other
   classes in the creation of DDS applications.

*/

#include "DDSCommunicator.hpp"

using namespace std;
// ------------------------------------------------------------------------- //
// Default constructor. Creates a QoS Provider, Participant, Publisher, and
// Subscriber based on the default profile in the default QoS file.
// ------------------------------------------------------------------------- //
// Creating a QosProvider
//
// A QoS provider allows access to qos profiles and the ability to choose and
// modify them.
// ------------------------------------------------------------------------- //
// Creating a DomainParticipant
//
// A DomainParticipant starts the DDS discovery process.  It creates
// several threads, sends and receives discovery information over one or
// more transports, and maintains an in-memory discovery database of
// remote DomainParticipants, remote DataWriters, and remote DataReaders
//
// Quality of Service can be applied on the level of the DomainParticipant.
// This QoS controls the characteristics of:
// 1. Transport properties such as which type of network (UDPv4, UDPv6,
//    shared memory) or which network interfaces it is allowed to use
// 2. Which applications this discovers.  By default, apps will discover
//    other DDS applications over multicast, loopback, and shared memory.
// 3. Resource limits for the DomainParticipant
//
// For more information on participant QoS, see the USER_QOS_PROFILES.xml
// file
// ------------------------------------------------------------------------- //
DDSCommunicator::DDSCommunicator()
{
    _qos = new dds::core::QosProvider(dds::core::null);
    *_qos = dds::core::QosProvider::Default();

    _participant = new dds::domain::DomainParticipant(0);
    _pub = new dds::pub::Publisher(*_participant);
    _sub = new dds::sub::Subscriber(*_participant);
}
DDSCommunicator::DDSCommunicator(std::string& qosFile)
{ 
    _qos = new dds::core::QosProvider(qosFile);
    _participant = new dds::domain::DomainParticipant(0, _qos->participant_qos());
    _pub = new dds::pub::Publisher(*_participant, _qos->publisher_qos());
    _sub = new dds::sub::Subscriber(*_participant, _qos->subscriber_qos());
}
DDSCommunicator::DDSCommunicator(std::string& qosFile, std::string& profile)
{ 
    _qos = new dds::core::QosProvider(qosFile, profile);
    _participant = new dds::domain::DomainParticipant(0, _qos->participant_qos(profile));
    _pub = new dds::pub::Publisher(*_participant, _qos->publisher_qos(profile));
    _sub = new dds::sub::Subscriber(*_participant, _qos->subscriber_qos(profile));
}
DDSCommunicator::DDSCommunicator(dds::core::StringSeq& qosFiles)
{ 
    ostringstream fileString;
    if (!qosFiles.empty()) {
        copy(qosFiles.begin(), qosFiles.end() - 1, ostream_iterator<string>(fileString, "; "));
        fileString << qosFiles.back();
    }

    _qos = new dds::core::QosProvider(fileString.str());
    _participant = new dds::domain::DomainParticipant(0, _qos->participant_qos());
    _pub = new dds::pub::Publisher(*_participant, _qos->publisher_qos());
    _sub = new dds::sub::Subscriber(*_participant, _qos->subscriber_qos());
}
DDSCommunicator::DDSCommunicator(std::vector<std::string>& qosFiles, std::string& profile)
{
    ostringstream fileString;
    if (!qosFiles.empty()) {
        copy(qosFiles.begin(), qosFiles.end() - 1, ostream_iterator<string>(fileString, "; "));
        fileString << qosFiles.back();
    }

    _qos = new dds::core::QosProvider(fileString.str());
    _participant = new dds::domain::DomainParticipant(0, _qos->participant_qos(profile));
    _pub = new dds::pub::Publisher(*_participant, _qos->publisher_qos(profile));
    _sub = new dds::sub::Subscriber(*_participant, _qos->subscriber_qos(profile));
}


// ------------------------------------------------------------------------- //
// Destruction of a DDS communication interface.  This first deletes all the
// entities created by the DomainParticipant object.  Then, it cleans up the
// types that have been registered with the DomainParticipant.  (This is not
// strictly necessary, but will cause a very small memory leak at shutdown if
// all types are not unregistered.  Thirdly, this deletes the
// DomainParticipant.  Lastly, this finalizes the DomainParticipantFactory.
DDSCommunicator::~DDSCommunicator()
{
    if (_participant != dds::core::null) {
        // RTI Connext provides a finalize_participant_factory() method if you
        // want to release memory used by the participant factory singleton.
        _participant->finalize_participant_factory();
    }
}

// ------------------------------------------------------------------------- //
// Getters for QoS, Publisher, and Subscriber.
dds::core::QosProvider& DDSCommunicator::Qos() const
{
    return *_qos;
}

dds::domain::DomainParticipant& DDSCommunicator::Participant() const
{
    return *_participant;
}

dds::pub::Publisher& DDSCommunicator::Publisher() const
{
    return *_pub;
}
dds::sub::Subscriber& DDSCommunicator::Subscriber() const
{
    return *_sub;
}
