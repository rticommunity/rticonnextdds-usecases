/*
 * (c) Copyright, Real-Time Innovations, 2025.  All rights reserved.
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the software solely for use with RTI Connext DDS. Licensee may
 * redistribute copies of the software provided that all such copies are subject
 * to this license. The software is provided "as is", with no warranty of any
 * type, including any warranty for fitness for any purpose. RTI is under no
 * obligation to maintain or support the software. RTI shall not be liable for
 * any incidental or consequential damages arising out of the use or inability
 * to use the software.
 */

#include <iostream>
#include <vector>
#include <climits>
#include <functional>
#include <random>
#include <chrono>
#include <thread>
#include <dds/pub/ddspub.hpp>
#include <rti/config/Logger.hpp>  // for logging
#include "application.hpp"        // for command line parsing and ctrl-c
#include "telemetry.hpp"

using MetricType = Metrics::MetricType;

static std::mt19937 twister;
static std::uniform_real_distribution<double> distribution(1, 999);

static void AddLabel(
        ::Metrics::Metric& metric,
        const std::string& key,
        const std::string& value)
{
    ::Metrics::Label label(key, value);

    if (metric.labels().has_value()) {
        metric.labels().value().push_back(label);
    } else {
        metric.labels() = { label };
    }
}

void PublishUint64Counter(
        dds::pub::DataWriter<::Metrics::Metric>& writer,
        const int counter)
{
    uint64_t val = counter;

    ::Metrics::Metric metric;
    metric.name("rti.example.uint64.counter");
    metric.description("Example UInt64 Counter");
    metric.unit("Jiffy");
    metric.data()._d(MetricType::UInt64CounterMetric);
    metric.data().uint64_counter().value(val);

    // Add a label to to test sending metric quality and/or other attributes
    // from the client
    AddLabel(
            metric,
            "status",
            (val <= 1000                         ? "good"
                     : val > 1000 && val <= 5000 ? "warning"
                                                 : "error"));

    writer.write(metric);

    std::cout << "Wrote: " << metric << std::endl;
}

void PublishDoubleCounter(
        dds::pub::DataWriter<::Metrics::Metric>& writer,
        const int counter)
{
    double val = (distribution(twister) / 1000) + static_cast<double>(counter);

    ::Metrics::Metric metric;
    metric.name("rti.example.double.counter");
    metric.description("Example Double Counter");
    metric.unit("Micro-Fortnight");
    metric.data()._d(MetricType::DoubleCounterMetric);
    metric.data().double_counter().value(val);

    AddLabel(
            metric,
            "status",
            (val <= 1000                         ? "good"
                     : val > 1000 && val <= 5000 ? "warning"
                                                 : "error"));

    writer.write(metric);

    std::cout << "Wrote: " << metric << std::endl;
}

void PublishUInt64Histogram(
        dds::pub::DataWriter<::Metrics::Metric>& writer,
        const int counter)
{
    ::Metrics::Metric metric;
    metric.name("rti.example.uint64.histogram");
    metric.description("Example UInt64 Histogram");
    metric.unit("Milliblatt");
    metric.data()._d(MetricType::UInt64HistogramMetric);

    for (uint32_t i = 0; i < 5; ++i) {
        ::Metrics::Label label;
        label.key("key" + std::to_string(i));
        label.value("value" + std::to_string(i));
        metric.data().uint64_histogram().labels().push_back(label);
    }

    for (uint32_t i = 0; i < 20; ++i) {
        metric.data().uint64_histogram().buckets().push_back(
                counter + static_cast<int>(distribution(twister)));
    }

    writer.write(metric);
    std::cout << "Wrote: " << metric << std::endl;
}

void PublishDoubleHistogram(
        dds::pub::DataWriter<::Metrics::Metric>& writer,
        const int counter)
{
    ::Metrics::Metric metric;
    metric.name("rti.example.double.histogram");
    metric.description("Example Double Histogram");
    metric.unit("Light-nanosecond");
    metric.data()._d(MetricType::DoubleHistogramMetric);

    for (uint32_t i = 0; i < 5; ++i) {
        ::Metrics::Label label;
        label.key("key" + std::to_string(i));
        label.value("value" + std::to_string(i));
        metric.data().double_histogram().labels().push_back(label);
    }

    for (uint32_t i = 0; i < 20; ++i) {
        metric.data().double_histogram().buckets().push_back(
                (distribution(twister) / 1000) + static_cast<double>(counter));
    }

    writer.write(metric);
    std::cout << "Wrote: " << metric << std::endl;
}

static bool counting_up = true;
static int64_t counter_uint = 0;

void PublishUInt64UpDownCounter(
        dds::pub::DataWriter<::Metrics::Metric>& writer,
        const int counter)
{
    if (0 == counter % 100) {
        counting_up = !counting_up;
    }
    counter_uint = counting_up ? counter_uint + 1 : counter_uint - 1;

    ::Metrics::Metric metric;
    metric.name("rti.example.uint64.updowncounter");
    metric.description("Example UInt64 UpDownCounter");
    metric.unit("Sheppey");
    metric.data()._d(MetricType::UInt64UpDownCounterMetric);
    metric.data().uint64_updown_counter().value(counter_uint);

    AddLabel(
            metric,
            "status",
            (counter_uint <= 1000                                  ? "good"
                     : counter_uint > 1000 && counter_uint <= 5000 ? "warning"
                                                                   : "error"));

    writer.write(metric);

    std::cout << "Wrote: " << metric << std::endl;
}

static double counter_double = (distribution(twister) / 1000);

void PublishDoubleUpDownCounter(
        dds::pub::DataWriter<::Metrics::Metric>& writer,
        const int counter)
{
    if (0 == counter % 100) {
        counting_up = !counting_up;
    }
    counter_double = counting_up ? counter_double + 0.1 : counter_double - 0.1;

    ::Metrics::Metric metric;
    metric.name("rti.example.double.updowncounter");
    metric.description("Example Double UpDownCounter");
    metric.unit("Muggeseggele");
    metric.data()._d(MetricType::DoubleUpDownCounterMetric);
    metric.data().double_updown_counter().value(counter_double);

    AddLabel(
            metric,
            "status",
            (counter_double <= 1000 ? "good"
                     : counter_double > 1000 && counter_double <= 5000
                     ? "warning"
                     : "error"));

    writer.write(metric);

    std::cout << "Wrote: " << metric << std::endl;
}

void PublishInt64Gauge(
        dds::pub::DataWriter<::Metrics::Metric>& writer,
        const int counter)
{
    int64_t val = static_cast<int64_t>(distribution(twister));

    ::Metrics::Metric metric;
    metric.name("rti.example.int64.gauge");
    metric.description("Example Int64 Gauge");
    metric.unit("Gloops");
    metric.data()._d(MetricType::Int64GaugeMetric);
    metric.data().int64_gauge().value(val);

    AddLabel(
            metric,
            "status",
            (val <= 333                        ? "good"
                     : val > 333 && val <= 666 ? "warning"
                                               : "error"));

    writer.write(metric);

    std::cout << "Wrote: " << metric << std::endl;
}

void PublishDoubleGauge(
        dds::pub::DataWriter<::Metrics::Metric>& writer,
        const int counter)
{
    double val = (distribution(twister) / 1000) + static_cast<double>(counter);
    if (counter % 2 == 0)
        val = val - distribution(twister);
    else
        val = val + distribution(twister);

    ::Metrics::Metric metric;
    metric.name("rti.example.double.gauge");
    metric.description("Example Double Gauge");
    metric.unit("MegaFonzie");
    metric.data()._d(MetricType::DoubleGaugeMetric);
    metric.data().double_gauge().value(val);

    AddLabel(
            metric,
            "status",
            (val <= 333                        ? "good"
                     : val > 333 && val <= 666 ? "warning"
                                               : "error"));

    writer.write(metric);

    std::cout << "Wrote: " << metric << std::endl;
}

void run_publisher_application(
        unsigned int domain_id,
        const std::string& qos_file,
        unsigned int sample_count)
{
    dds::core::QosProvider qos_provider(qos_file);

    // Start communicating in a domain, usually one participant per application
    dds::domain::DomainParticipant participant(
            domain_id,
            qos_provider.participant_qos());

    // Create a Topic with a name and a datatype
    dds::topic::Topic<::Metrics::Metric> topic(
            participant,
            "Application Telemetry");

    // Create a Publisher
    dds::pub::Publisher publisher(participant);

    // Create a DataWriter with default QoS
    dds::pub::DataWriter<::Metrics::Metric> writer(
            publisher,
            topic,
            qos_provider.datawriter_qos(
                    "telemetry_library::telemetry_profile"));

    std::vector<std::function<
            void(dds::pub::DataWriter<::Metrics::Metric>&, const int)>>
            functions = {
                PublishUint64Counter,       PublishDoubleCounter,
                PublishUInt64Histogram,     PublishDoubleHistogram,
                PublishUInt64UpDownCounter, PublishDoubleUpDownCounter,
                PublishInt64Gauge,          PublishDoubleGauge
            };

    // Main loop, publish telemetry data
    for (unsigned int samples_written = 0, idx = 0;
         !application::shutdown_requested && samples_written < sample_count;
         ++samples_written, idx = (idx + 1) % functions.size()) {
        functions[idx](writer, samples_written);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char *argv[])
{
    using namespace application;

    // Parse arguments and handle control-C
    auto arguments = parse_arguments(argc, argv);
    if (arguments.parse_result == ParseReturn::exit) {
        return EXIT_SUCCESS;
    } else if (arguments.parse_result == ParseReturn::failure) {
        return EXIT_FAILURE;
    }
    setup_signal_handlers();

    // Sets Connext verbosity to help debugging
    rti::config::Logger::instance().verbosity(arguments.verbosity);

    // Initialize random seed
    std::random_device rd;
    unsigned seed = rd.entropy()
            ? rd()
            : static_cast<unsigned>(std::chrono::system_clock::now()
                                            .time_since_epoch()
                                            .count());
    twister.seed(seed);

    try {
        run_publisher_application(
                arguments.domain_id,
                arguments.qos_file,
                arguments.sample_count);
    } catch (const std::exception& ex) {
        // This will catch DDS exceptions
        std::cerr << "Exception in run_publisher_application(): " << ex.what()
                  << std::endl;
        return EXIT_FAILURE;
    }

    // Releases the memory used by the participant factory.  Optional at
    // application exit
    dds::domain::DomainParticipant::finalize_participant_factory();

    return EXIT_SUCCESS;
}
