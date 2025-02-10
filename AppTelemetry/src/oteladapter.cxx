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
#include <memory>

#include "oteladapter.hpp"
#include "otelconnection.hpp"
#include <rti/routing/Logger.hpp>

using namespace rti::routing;
using namespace rti::routing::adapter;

OpenTelemetryAdapter::OpenTelemetryAdapter(PropertySet &)
{}

Connection *OpenTelemetryAdapter::create_connection(
        rti::routing::adapter::detail::StreamReaderListener *,
        rti::routing::adapter::detail::StreamReaderListener *,
        const PropertySet &properties)
{
    std::cout << "Creating OpenTelemetry connection" << std::endl;
    return new OpenTelemetryConnection(properties);
}

void OpenTelemetryAdapter::delete_connection(Connection *connection)
{
    delete connection;
}

rti::config::LibraryVersion OpenTelemetryAdapter::get_version() const
{
    return { 1, 0, 0, 'r' };
};

RTI_ADAPTER_PLUGIN_CREATE_FUNCTION_DEF(OpenTelemetryAdapter)