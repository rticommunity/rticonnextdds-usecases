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

#include <dds/core/macros.hpp>
#include <rti/routing/adapter/AdapterPlugin.hpp>
#include <rti/routing/adapter/Connection.hpp>

class OpenTelemetryStreamWriter;

class OpenTelemetryConnection : public rti::routing::adapter::Connection {
public:
    /**
     * @brief Creates the connection given its configuration properites
     * @param properties
     *      Configuration properites provided by the <property> tag within
     *      <connection>.
     *
     */
    OpenTelemetryConnection(const rti::routing::PropertySet &properties);
    ~OpenTelemetryConnection();

    /*
     * --- Connection interface
     * ---------------------------------------------------------
     */
    rti::routing::adapter::StreamWriter *create_stream_writer(
            rti::routing::adapter::Session *session,
            const rti::routing::StreamInfo &info,
            const rti::routing::PropertySet &properties) override final;

    void delete_stream_writer(
            rti::routing::adapter::StreamWriter *writer) override final;

private:
    friend OpenTelemetryStreamWriter;

};