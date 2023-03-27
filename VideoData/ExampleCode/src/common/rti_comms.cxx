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
#include "rti_comms.hpp"

 /** ----------------------------------------------------------------
  * tstamp_u64_get()
  * utility timestamp getter
  **/
uint64_t tstamp_u64_get(void)
{
    timespec tStamp;
#ifdef WIN32
    timespec_get(&tStamp, TIME_UTC);
#else
    clock_gettime(CLOCK_REALTIME, &tStamp);
#endif
    return (uint64_t)(((uint64_t)tStamp.tv_sec * 1000000000) + tStamp.tv_nsec);
}


rtiComms::rtiComms(
    const std::string topicName, uint32_t opt_en, 
    dds::domain::DomainParticipant participant,
    dds::core::cond::WaitSet *waitset_ext,
    int(*rcv_fptr)(dds::sub::DataReader<cctypes::ccBulk>))
    :
    data_topic(dds::core::null), pub_sample(), sub_sample(),
    data_wr(dds::core::null), data_rd(dds::core::null),
    waitset_int(), waitset()    
{ 
    // create topic
    data_topic = dds::topic::Topic<cctypes::ccBulk>(participant, topicName);

    // publisher
    if (opt_en & CTRL_PUB_BE) {
        // DataWriter
#if 0   // bounded
        data_wr = dds::pub::DataWriter<cctypes::ccBulk>(dds::pub::Publisher(participant), data_topic);
#else   // unbounded or bounded support
        dds::pub::qos::DataWriterQos writer_qos = dds::core::QosProvider::Default().datawriter_qos();
        writer_qos.policy<rti::core::policy::Property>().set({ "dds.data_writer.history.memory_manager.fast_pool.pool_buffer_max_size", "1048576" });
        data_wr = dds::pub::DataWriter<cctypes::ccBulk>(dds::pub::Publisher(participant), data_topic, writer_qos);
#endif
    }

    // subscriber
    if (opt_en & CTRL_SUB_BE) {
        // DataReader, ReadCondition, WaitSet
        data_rd = dds::sub::DataReader<cctypes::ccBulk>(dds::sub::Subscriber(participant), data_topic);
        dds::sub::cond::ReadCondition data_readCond(
            data_rd, dds::sub::status::DataState::any(),
            [rcv_fptr, this](/* dds::core::cond::Condition condition */)
        {
            if (rcv_fptr == NULL) {
                // use the default receive handler if no other was specified
                data_rcv_count += rcv_dataProc(data_rd);
            }
            else {
                // use the specified receive handler
                data_rcv_count += rcv_fptr(data_rd);
            }
        }
        );
        if(waitset_ext == NULL) {
            waitset = &waitset_int;
        }
        else {
            waitset = waitset_ext;
        }
        *waitset += data_readCond;
        data_rcv_count = 0;
    }
}

// Built-in receive data handler (not used if rcv_fptr was provided at class instantiation)
int rtiComms::rcv_dataProc(dds::sub::DataReader<cctypes::ccBulk >& reader)
{
    int count = 0;
    dds::sub::LoanedSamples<cctypes::ccBulk> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            //std::cout << "PoseCtrl " << sample.data() << std::endl;
            sub_samples.push(sample);
            count++;
        }
    }
    //std::cout <<  std::endl;
    return count;
}

/*ci
 * \brief Publish the ccBulk_ topic.
 */
void rtiComms::publish(void)
{
    //pub_sample.tstamp_first_frame(tstamp_u64_get());
    data_wr.write(pub_sample);
}

void rtiComms::publish(cctypes::ccBulk sample)
{
    //sample.tstamp_first_frame(tstamp_u64_get());
    data_wr.write(sample);
}


// destructor
rtiComms::~rtiComms() {}

