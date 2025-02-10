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

#include <string>
#include <chrono>
#include <rti/routing/Logger.hpp>
#include "opentelemetry/exporters/prometheus/exporter_factory.h"
#include "opentelemetry/exporters/prometheus/exporter_options.h"
#include "opentelemetry/metrics/provider.h"
#include <opentelemetry/metrics/meter.h>
#include "opentelemetry/sdk/metrics/meter_provider.h"
#include "opentelemetry/sdk/metrics/meter_provider_factory.h"
#include "otelconfig.hpp"
#include "otelconnection.hpp"
#include "otelstreamwriter.hpp"

using namespace rti::routing;
using namespace rti::routing::adapter;

using rti::routing::PropertySet;
using rti::routing::Logger;
using std::string;

namespace metrics_api = opentelemetry::metrics;
namespace metrics_sdk = opentelemetry::sdk::metrics;
namespace metrics_exporter = opentelemetry::exporter::metrics;

OpenTelemetryConnection::OpenTelemetryConnection(const PropertySet &properties)
{      
    metrics_exporter::PrometheusExporterOptions options;

    OpenTelemetryConfig config;
    if (config.GetValue<bool>(properties, keys::EXPORT_DEBUG, false)) {
        Logger::instance().service_verbosity(rti::config::Verbosity::WARNING);
    }    
    
    if (!config.GetValue<std::string>(properties, keys::PROMETHEUS_SCRAPE_URL, options.url)) {
        Logger::instance().error("OpenTelemetryConnection: No URL provided for Prometheus exporter");
        throw dds::core::InvalidArgumentError(
                "Prometheus scrape URL is mandatory (property name: "
                + keys::ToStr[keys::PROMETHEUS_SCRAPE_URL]);
        return;
    }
    
    auto prometheus_exporter = metrics_exporter::PrometheusExporterFactory::Create(options);
    
    // Initialize and set the global MeterProvider
    auto u_provider = metrics_sdk::MeterProviderFactory::Create();
    auto *p = static_cast<metrics_sdk::MeterProvider *>(u_provider.get());
    p->AddMetricReader(std::move(prometheus_exporter));

    // Set the global Meter Provider
    std::shared_ptr<opentelemetry::metrics::MeterProvider> provider(std::move(u_provider));
    metrics_api::Provider::SetMeterProvider(provider);
}

OpenTelemetryConnection::~OpenTelemetryConnection()
{
    std::shared_ptr<metrics_api::MeterProvider> none;
    metrics_api::Provider::SetMeterProvider(none);
}

/// Adapter Interface
StreamWriter *OpenTelemetryConnection::create_stream_writer(
        Session *,
        const StreamInfo &stream_info,
        const PropertySet &properties)
{
    return new OpenTelemetryStreamWriter(*this, stream_info, properties);
};

void OpenTelemetryConnection::delete_stream_writer(StreamWriter *writer)
{
    delete writer;
}
