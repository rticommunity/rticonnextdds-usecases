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

#include <sstream>
#include <string>
#include <stdexcept>
#include <rti/routing/Logger.hpp>
#include <rti/routing/PropertySet.hpp>

namespace keys {
    enum Enum {
        PROMETHEUS_SCRAPE_URL,
        EXPORT_DEBUG,
    };

    const std::string ToStr[] = {
        "Prometheus.scrape_url",
        "OpenTelemetry.debug",
    };
};

class OpenTelemetryConfig {
public:
    
    template <typename T>
    bool GetValue(const rti::routing::PropertySet &properties, const keys::Enum& key, T& value) {
         bool result = false;

        rti::routing::PropertySet::const_iterator it = properties.find(keys::ToStr[key]);
        if (it != properties.end())
            result = this->StringToType<T>(it->second, value);

        return result;
    }

    template <typename T>
    T GetValue(const rti::routing::PropertySet &properties, const keys::Enum& key) {
        T tmp;
        GetValue<T>(properties, key, tmp);
        return tmp;
    }
        
    template <typename T>
    T GetValue(const rti::routing::PropertySet &properties, const keys::Enum& key, const T& defaultValue) {
        T tmp = defaultValue;
        GetValue<T>(properties, key, tmp);
        return tmp;
    }

protected:
    template <typename T>
    bool StringToType(const std::string& before, T& after) {
        bool result = false;
        std::istringstream ss(before);
        if (!ss.str().empty()) {
            ss >> after;
            result = true;
        }

        return result;
    }
};

template <> // string to int
bool OpenTelemetryConfig::StringToType(const std::string& before, int& after) {
    bool result = false;
    try {
        after = std::stoi(before);
        result = true;
    } 
    catch (std::invalid_argument &e) {
        std::ostringstream oss;
                
        oss << "Invalid argument: " << e.what();
        rti::routing::Logger::instance().warn(oss.str());
    }
    catch (std::out_of_range &e) {
        std::ostringstream oss;

        oss << "Out of range: " << e.what();
        rti::routing::Logger::instance().warn(oss.str());
    }
    return result;
}

template <> // string to bool
bool OpenTelemetryConfig::StringToType(const std::string& before, bool& after) {

    bool result = false;

    std::string::size_type eq = before.find_first_of("TtYy1");
    if (std::string::npos != eq)
        result = after = true;
    else {
        eq = before.find_first_of("FfNn0");
        if (std::string::npos != eq) {
            result = true;
            after = false;
        }
    }

    return result;
}

template <> // string to string
bool OpenTelemetryConfig::StringToType(const std::string& before, std::string& after) {
    after = before;
    return true;
}
