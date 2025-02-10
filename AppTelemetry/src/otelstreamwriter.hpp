/*
 * (c) 2024 Copyright, Real-Time Innovations, Inc.  All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the Software.  Licensee has the right to distribute object form
 * only for use with RTI products.  The Software is provided "as is", with no
 * warranty of any type, including any warranty for fitness for any purpose.
 * RTI is under no obligation to maintain or support the Software.  RTI shall
 * not be liable for any incidental or consequential damages arising out of the
 * use or inability to use the software.
 */
#pragma once

#include <string>

#include <rti/routing/adapter/AdapterPlugin.hpp>
#include <rti/routing/adapter/StreamWriter.hpp>
#include "otelconnection.hpp"

class OpenTelemetryStreamWriter
        : public rti::routing::adapter::DynamicDataStreamWriter {
public:
    OpenTelemetryStreamWriter(
            OpenTelemetryConnection &connection,
            const rti::routing::StreamInfo &stream_info,
            const rti::routing::PropertySet &properties);

    int write(
            const std::vector<dds::core::xtypes::DynamicData *> &samples,
            const std::vector<dds::sub::SampleInfo *> &infos) override final;

private:
    OpenTelemetryConnection &_connection;
    std::string _stream_name;
};
