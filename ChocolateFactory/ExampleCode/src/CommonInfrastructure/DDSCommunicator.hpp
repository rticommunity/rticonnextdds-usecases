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

/* DDSCommunicator.h

   Defines common DDS communication elements that are to be inherited by other
   classes in the creation of DDS applications.

*/

#ifndef DDS_COMMUNICATOR_H
#define DDS_COMMUNICATOR_H

#include <sstream>
#include <vector>
#include <map>

#include <dds/dds.hpp>

// ------------------------------------------------------------------------- //
//
// DDSCommunicator:
// This class is used by all RTI Connext DDS interfaces to create the core
// communication objects, such as a DomainParticipant, Publisher and/or
// Subscriber.
//
// ------------------------------------------------------------------------- //
class DDSCommunicator {
public:
    // --- Constructor and Destructor ---
    DDSCommunicator();
    DDSCommunicator(std::string& qosFile);
    DDSCommunicator(std::string& qosFiles, std::string& profile);
    DDSCommunicator(dds::core::StringSeq& qosFiles);
    DDSCommunicator(std::vector<std::string>& qosFiles, std::string& profile);

    ~DDSCommunicator();

    // --- Data element Getters ---

    // These getter functions allow classes that use the DDS Communicator class
    // to pull the QoS, Publisher, and Subscriber to create DataReaders and
    // DataWriters

    dds::core::QosProvider& Qos();
    dds::domain::DomainParticipant& Participant();
    dds::pub::Publisher& Publisher();
    dds::sub::Subscriber& Subscriber();

private:
    // --- Protected members ---

    // Used to create a QOS Provider to be used by other elements
    dds::core::QosProvider* _qos;

    // Used to create other DDS entities
    dds::domain::DomainParticipant* _participant;

    // Used to create DataWriters
    dds::pub::Publisher* _pub;

    // Used to create DataReaders
    dds::sub::Subscriber* _sub;
};


#endif
