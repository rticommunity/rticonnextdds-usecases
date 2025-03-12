/*
 * (c) 2025 Copyright, Real-Time Innovations, Inc.  All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the Software.  Licensee has the right to distribute object form
 * only for use with RTI products.  The Software is provided "as is", with no
 * warranty of any type, including any warranty for fitness for any purpose.
 * RTI is under no obligation to maintain or support the Software.  RTI shall
 * not be liable for any incidental or consequential damages arising out of the
 * use or inability to use the software.
 */


#include <iostream>
#include <sstream>
#include <map>

#include <rti/routing/Logger.hpp>
#include <rti/topic/to_string.hpp>
#include <dds/core/ddscore.hpp>
#include <dds/core/xtypes/DynamicData.hpp>
#include <dds/core/xtypes/DynamicType.hpp>

#include <rti/core/xtypes/DynamicDataImpl.hpp>

#include <dds/sub/SampleInfo.hpp>
#include <opentelemetry/metrics/provider.h>
#include <opentelemetry/metrics/meter.h>
#include <opentelemetry/sdk/metrics/meter_provider.h>

#include "otelstreamwriter.hpp"

using namespace rti::routing;
using namespace rti::routing::adapter;

namespace metrics_api = opentelemetry::metrics;

using rti::routing::Logger;
using std::exception;
using std::map;
using std::ostringstream;
using std::string;
using std::vector;

using stringmap_t = map<string, string>;

static const char endl = '\n';

namespace MetricTypes {
enum Enum {
    UInt64Counter = 0,
    DoubleCounter = 1,
    UInt64Histogram = 2,
    DoubleHistogram = 3,
    UInt64UpDownCounter = 4,
    DoubleUpDownCounter = 5,
    Int64Gauge = 6,
    DoubleGauge = 7
};
}

OpenTelemetryStreamWriter::OpenTelemetryStreamWriter(
        OpenTelemetryConnection& connection,
        const StreamInfo& stream_info,
        const PropertySet&)
        : _connection(connection), _stream_name(stream_info.stream_name())
{
    Logger::instance().local(
            "created StreamWriter for stream: " + _stream_name);
}

static void read_labels(
        const dds::core::xtypes::DynamicData& source_data,
        stringmap_t& labels)
{
    // Access the sequence of labels
    const dds::core::xtypes::DynamicData& labels_data =
            source_data.value<dds::core::xtypes::DynamicData>("labels");

    // Iterate over the sequence
    for (uint32_t i = 0; i < labels_data.member_count(); ++i) {
        // Access each label
        const dds::core::xtypes::DynamicData& label_data =
                labels_data.value<dds::core::xtypes::DynamicData>(i + 1);

        // Read the key and value fields
        std::string key = label_data.value<std::string>("key");
        std::string value = label_data.value<std::string>("value");

        // Insert into the map
        labels[key] = value;
    }
}

int OpenTelemetryStreamWriter::write(
        const vector<dds::core::xtypes::DynamicData *>& samples,
        const vector<dds::sub::SampleInfo *>& infos)
{
    auto provider = metrics_api::Provider::GetMeterProvider();

    for (auto sample : samples) {
        try {
            // Log the received sample
            ostringstream oss;
            oss << "Received Sample: " << endl
                << rti::topic::to_string(*sample);
            Logger::instance().debug(oss.str());

            // Access the Metric data
            string name = sample->value<string>("name");
            string description = sample->value<string>("description");
            string unit = sample->value<string>("unit");

            // Add optional fields based on attibutes (metric quality, etc.)
            stringmap_t optional_labels;
            if (sample->member_exists("labels")) {
                auto loaned_labels = sample->loan_value("labels");

                for (uint32_t i = 0; i < loaned_labels.get().member_count();
                     ++i) {
                    auto label_element = loaned_labels.get().loan_value(i + 1);

                    // Read the key and value fields
                    std::string key =
                            label_element.get().value<std::string>("key");
                    std::string value =
                            label_element.get().value<std::string>("value");

                    // Insert into the map
                    optional_labels[key] = value;
                }

                loaned_labels.return_loan();
            }

            auto loaned_data = sample->loan_value("data");
            const dds::core::xtypes::DynamicData& with = loaned_data.get();

            // Process the union based on the discriminator
            const auto& discriminator = with.discriminator_value();
            switch (discriminator) {
            case MetricTypes::UInt64Counter: {
                const dds::core::xtypes::DynamicData& with2 =
                        with.value<dds::core::xtypes::DynamicData>(
                                "uint64_counter");

                // Read the value field
                uint64_t value = with2.value<uint64_t>("value");

                opentelemetry::nostd::shared_ptr<metrics_api::Meter> meter =
                        provider->GetMeter(name, "1.2.0");
                auto counter =
                        meter->CreateUInt64Counter(name, description, unit);

                if (optional_labels.empty())
                    counter->Add(value);
                else {
                    auto context = opentelemetry::context::Context {};
                    auto labelkv = opentelemetry::common::KeyValueIterableView<
                            decltype(optional_labels)> { optional_labels };
                    counter->Add(value, labelkv, context);
                }
            } break;

            case MetricTypes::DoubleCounter: {
                const dds::core::xtypes::DynamicData& with2 =
                        with.value<dds::core::xtypes::DynamicData>(
                                "double_counter");

                // Read the value field
                double value = with2.value<double>("value");

                opentelemetry::nostd::shared_ptr<metrics_api::Meter> meter =
                        provider->GetMeter(name, "1.2.0");
                auto counter =
                        meter->CreateDoubleCounter(name, description, unit);

                if (optional_labels.empty())
                    counter->Add(value);
                else {
                    auto context = opentelemetry::context::Context {};
                    auto labelkv = opentelemetry::common::KeyValueIterableView<
                            decltype(optional_labels)> { optional_labels };
                    counter->Add(value, labelkv, context);
                }
            } break;

            case MetricTypes::UInt64Histogram: {
                const dds::core::xtypes::DynamicData& with2 =
                        with.value<dds::core::xtypes::DynamicData>(
                                "uint64_histogram");

                const dds::core::xtypes::DynamicData& bucket_data =
                        with2.value<dds::core::xtypes::DynamicData>("buckets");

                std::vector<uint64_t> buckets = {};
                buckets.reserve(bucket_data.member_count());

                // Iterate over the sequence
                for (uint32_t i = 0; i < bucket_data.member_count(); ++i) {
                    uint64_t value = bucket_data.value<uint64_t>(i + 1);
                    buckets.push_back(value);
                }

                // RTIOsapiLibrary_openEx:!open library=liboteladapter.so:
                // liboteladapter.so: undefined symbol:
                // _ZNK3rti4core6xtypes15DynamicDataImpl10get_valuesImEEvRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSt6vectorIT_SaISD_EE
                // with2.get_values("buckets", buckets);

                // Build up the label map
                stringmap_t labels;
                read_labels(with2, labels);

                opentelemetry::nostd::shared_ptr<metrics_api::Meter> meter =
                        provider->GetMeter(name, "1.2.0");
                auto histogram =
                        meter->CreateUInt64Histogram(name, description, unit);
                auto context = opentelemetry::context::Context {};
                auto labelkv = opentelemetry::common::KeyValueIterableView<
                        decltype(labels)> { labels };

                for (auto bucket : buckets) {
                    histogram->Record(bucket, labelkv, context);
                }
            } break;

            case MetricTypes::DoubleHistogram: {
                const dds::core::xtypes::DynamicData& with2 =
                        with.value<dds::core::xtypes::DynamicData>(
                                "double_histogram");

                const dds::core::xtypes::DynamicData& bucket_data =
                        with2.value<dds::core::xtypes::DynamicData>("buckets");

                std::vector<double> buckets = {};
                buckets.reserve(bucket_data.member_count());

                // Iterate over the sequence
                for (uint32_t i = 0; i < bucket_data.member_count(); ++i) {
                    double value = bucket_data.value<double>(i + 1);
                    buckets.push_back(value);
                }

                // Build up the label map
                stringmap_t labels;
                read_labels(with2, labels);

                opentelemetry::nostd::shared_ptr<metrics_api::Meter> meter =
                        provider->GetMeter(name, "1.2.0");
                auto histogram =
                        meter->CreateDoubleHistogram(name, description, unit);
                auto context = opentelemetry::context::Context {};
                auto labelkv = opentelemetry::common::KeyValueIterableView<
                        decltype(labels)> { labels };
                for (auto bucket : buckets) {
                    histogram->Record(bucket, labelkv, context);
                }
            } break;

            case MetricTypes::UInt64UpDownCounter: {
                const dds::core::xtypes::DynamicData& with2 =
                        with.value<dds::core::xtypes::DynamicData>(
                                "uint64_updown_counter");

                // Read the value field
                uint64_t value = with2.value<uint64_t>("value");

                opentelemetry::nostd::shared_ptr<metrics_api::Meter> meter =
                        provider->GetMeter(name, "1.2.0");
                auto counter = meter->CreateInt64UpDownCounter(
                        name,
                        description,
                        unit);

                if (optional_labels.empty())
                    counter->Add(value);
                else {
                    auto context = opentelemetry::context::Context {};
                    auto labelkv = opentelemetry::common::KeyValueIterableView<
                            decltype(optional_labels)> { optional_labels };
                    counter->Add(value, labelkv, context);
                }
            } break;

            case MetricTypes::DoubleUpDownCounter: {  // DoubleUpDownCounter
                const dds::core::xtypes::DynamicData& with2 =
                        with.value<dds::core::xtypes::DynamicData>(
                                "double_updown_counter");

                // Read the value field
                double value = with2.value<double>("value");

                opentelemetry::nostd::shared_ptr<metrics_api::Meter> meter =
                        provider->GetMeter(name, "1.2.0");
                auto counter = meter->CreateDoubleUpDownCounter(
                        name,
                        description,
                        unit);
                if (optional_labels.empty())
                    counter->Add(value);
                else {
                    auto context = opentelemetry::context::Context {};
                    auto labelkv = opentelemetry::common::KeyValueIterableView<
                            decltype(optional_labels)> { optional_labels };
                    counter->Add(value, labelkv, context);
                }
            } break;

#if OPENTELEMETRY_ABI_VERSION_NO >= 2
            case MetricTypes::Int64Gauge: {  // Int64Gauge
                const dds::core::xtypes::DynamicData& with2 =
                        with.value<dds::core::xtypes::DynamicData>(
                                "int64_gauge");

                // Read the value field
                uint64_t value = with2.value<uint64_t>("value");

                opentelemetry::nostd::shared_ptr<metrics_api::Meter> meter =
                        provider->GetMeter(name, "1.2.0");
                auto gauge = meter->CreateInt64Gauge(name, description, unit);

                if (optional_labels.empty())
                    gauge->Record(value);
                else {
                    auto context = opentelemetry::context::Context {};
                    auto labelkv = opentelemetry::common::KeyValueIterableView<
                            decltype(optional_labels)> { optional_labels };
                    gauge->Record(value, labelkv, context);
                }
            } break;

            case MetricTypes::DoubleGauge: {  // DoubleGauge
                const dds::core::xtypes::DynamicData& with2 =
                        with.value<dds::core::xtypes::DynamicData>(
                                "double_gauge");

                // Read the value field
                double value = with2.value<double>("value");

                opentelemetry::nostd::shared_ptr<metrics_api::Meter> meter =
                        provider->GetMeter(name, "1.2.0");
                auto gauge = meter->CreateDoubleGauge(name, description, unit);

                if (optional_labels.empty())
                    gauge->Record(value);
                else {
                    auto context = opentelemetry::context::Context {};
                    auto labelkv = opentelemetry::common::KeyValueIterableView<
                            decltype(optional_labels)> { optional_labels };
                    gauge->Record(value, labelkv, context);
                }
            } break;
#endif
            }
            loaned_data.return_loan();

        } catch (const exception& ex) {
            ostringstream oss;

            oss << "Error writing samples: " << ex.what() << endl;
            Logger::instance().error(oss.str());
            return 0;
        }
    }

    return samples.size();
}