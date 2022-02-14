/*
* (c) Copyright, Real-Time Innovations, 2021. All rights reserved.
* RTI grants Licensee a license to use, modify, compile, and create derivative
* works of the software solely for use with RTI Connext DDS. Licensee may
* redistribute copies of the software provided that all such copies are subject
* to this license. The software is provided "as is", with no warranty of any
* type, including any warranty for fitness for any purpose. RTI is under no
* obligation to maintain or support the software. RTI shall not be liable for
* any incidental or consequential damages arising out of the use or inability
* to use the software.
*/
#ifndef __RTI_COMMS_HPP__
#define __RTI_COMMS_HPP__
#include <algorithm>
#include <iostream>
#include <queue>
#include <dds/pub/ddspub.hpp>
#include <dds/sub/ddssub.hpp>
#include <dds/core/ddscore.hpp>
#include <rti/util/util.hpp>        // for sleep()
#include <rti/config/Logger.hpp>    // for logging
#include "cc_str_com_types.hpp"     // datatype pub/sub (generated code)
// alternatively, to include all the standard APIs:
//  <dds/dds.hpp>
// or to include both the standard APIs and extensions:
//  <rti/rti.hpp>
//
// For more information about the headers and namespaces, see:
//    https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/api/connext_dds/api_cpp2/group__DDSNamespaceModule.html
// For information on how to use extensions, see:
//    https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/api/connext_dds/api_cpp2/group__DDSCpp2Conventions.html

// defines make more sense here (for a bitfield)
#define CTRL_PUB_BE         (1<<0)
#define CTRL_SUB_BE         (1<<1)
#define CTRL_PUB_REL        (1<<2)
#define CTRL_SUB_REL        (1<<3)

uint64_t tstamp_u64_get(void);

// rti_comms.hpp
// Class for streaming comms using RTI Connext 
class rtiComms
{
public:
    rtiComms(
        const std::string topicName, uint32_t opt_en, 
        dds::domain::DomainParticipant participant,
        dds::core::cond::WaitSet *waitset_ext = NULL,
        int(*rcv_fptr)(dds::sub::DataReader<cctypes::ccBulk>) = NULL);
    ~rtiComms();

    cctypes::ccBulk *get_pub_sample(void) { return &pub_sample; }
    void publish(void);
    void publish(cctypes::ccBulk sample);
    void datarcv_waitset(int32_t secs, uint32_t nsecs) { waitset->dispatch(dds::core::Duration(secs, nsecs)); }

    // pub sample element setters
    void pub_sample_pub_id_set(std::string id) {pub_sample.pub_id(id); }
    uint8_t *pub_sample_data(void) { return pub_sample.data().data(); }
    void pub_sample_data_size_set(int32_t newSize) { pub_sample.data().resize(newSize); }

    // sub sample
    cctypes::ccBulk pop_sub_sample(void) { 
        cctypes::ccBulk oldestSample = sub_samples.front();
        sub_samples.pop();
        return oldestSample;
    }
    cctypes::ccBulk oldest_sub_sample(void) { return sub_samples.front(); }
    uint32_t sub_samples_in_queue(void) { return (uint32_t)sub_samples.size(); }
    void pop_oldest_sub_sample(void) { sub_samples.pop(); }

private:
    // DDS Topic, DataWriter, DataReader, read data handler, sample
    dds::topic::Topic<cctypes::ccBulk> data_topic;
    dds::pub::DataWriter<cctypes::ccBulk> data_wr;
    dds::sub::DataReader<cctypes::ccBulk> data_rd;
    int rcv_dataProc(dds::sub::DataReader<cctypes::ccBulk> & reader);
    cctypes::ccBulk pub_sample;
    cctypes::ccBulk sub_sample;
    std::queue<cctypes::ccBulk> sub_samples;

    // misc
    dds::core::cond::WaitSet waitset_int;       // internal waitset (if no external provided)
    dds::core::cond::WaitSet *waitset;
    int32_t data_rcv_count;
};

#endif      // ndef __RTI_COMMS_HPP__
