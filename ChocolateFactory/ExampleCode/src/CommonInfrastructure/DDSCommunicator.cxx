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
    qos_ = new dds::core::QosProvider(dds::core::null);
    *qos_ = dds::core::QosProvider::Default();

    participant_ = new dds::domain::DomainParticipant(0);
    pub_ = new dds::pub::Publisher(*participant_);
    sub_ = new dds::sub::Subscriber(*participant_);
}
DDSCommunicator::DDSCommunicator(std::string& qosFile)
{
    qos_ = new dds::core::QosProvider(qosFile);
    participant_ = new dds::domain::DomainParticipant(0, qos_->participant_qos());
    pub_ = new dds::pub::Publisher(*participant_, qos_->publisher_qos());
    sub_ = new dds::sub::Subscriber(*participant_, qos_->subscriber_qos());
}
DDSCommunicator::DDSCommunicator(std::string& qosFile, std::string profile)
{
    qos_ = new dds::core::QosProvider(qosFile, profile);
    participant_ = new dds::domain::DomainParticipant(0, qos_->participant_qos(profile));
    pub_ = new dds::pub::Publisher(*participant_, qos_->publisher_qos(profile));
    sub_ = new dds::sub::Subscriber(*participant_, qos_->subscriber_qos(profile));
}
DDSCommunicator::DDSCommunicator(dds::core::StringSeq& qosFiles)
{
    ostringstream fileString;
    if (!qosFiles.empty()) {
        copy(qosFiles.begin(), qosFiles.end() - 1, ostream_iterator<string>(fileString, "; "));
        fileString << qosFiles.back();
    }

    qos_ = new dds::core::QosProvider(fileString.str());
    participant_ = new dds::domain::DomainParticipant(0, qos_->participant_qos());
    pub_ = new dds::pub::Publisher(*participant_, qos_->publisher_qos());
    sub_ = new dds::sub::Subscriber(*participant_, qos_->subscriber_qos());
}
DDSCommunicator::DDSCommunicator(std::vector<std::string>& qosFiles, std::string profile)
{
    ostringstream fileString;
    if (!qosFiles.empty()) {
        copy(qosFiles.begin(), qosFiles.end() - 1, ostream_iterator<string>(fileString, "; "));
        fileString << qosFiles.back();
    }

    qos_ = new dds::core::QosProvider(fileString.str());
    participant_ = new dds::domain::DomainParticipant(0, qos_->participant_qos(profile));
    pub_ = new dds::pub::Publisher(*participant_, qos_->publisher_qos(profile));
    sub_ = new dds::sub::Subscriber(*participant_, qos_->subscriber_qos(profile));
}


// ------------------------------------------------------------------------- //
// Destruction of a DDS communication interface.  This first deletes all the
// entities created by the DomainParticipant object.  Then, it cleans up the
// types that have been registered with the DomainParticipant.  (This is not
// strictly necessary, but will cause a very small memory leak at shutdown if
// all types are not unregistered.  Thirdly, this deletes the
// DomainParticipant.  Lastly, this finalizes the DomainParticipantFactory.
DDSCommunicator::~DDSCommunicator()
{ }

// ------------------------------------------------------------------------- //
// Getters for QoS, Publisher, and Subscriber.
dds::core::QosProvider& DDSCommunicator::Qos() const
{
    return *qos_;
}

dds::domain::DomainParticipant& DDSCommunicator::Participant() const
{
    return *participant_;
}

dds::pub::Publisher& DDSCommunicator::Publisher() const
{
    return *pub_;
}
dds::sub::Subscriber& DDSCommunicator::Subscriber() const
{
    return *sub_;
}
