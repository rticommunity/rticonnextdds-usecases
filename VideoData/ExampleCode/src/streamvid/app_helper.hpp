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
/**
 * app_helper.hpp -- derived from the 'application.hpp' file created by 
 * 'rtiddsgen' code generator application, customized for this example.
 **/

#ifndef __APP_HELPER_HPP__
#define __APP_HELPER_HPP__

#include <iostream>
#include <fstream>
#include <csignal>
#include <dds/core/ddscore.hpp>
#include "property_util.h"          // for reading from a named config/property file.


namespace application {

    // Catch control-C and tell application to shut down
    bool shutdown_requested = false;

    const std::string config_filename_default = "config.properties";

    inline void stop_handler(int)
    {
        shutdown_requested = true;
        std::cout << "preparing to shut down..." << std::endl;
    }

    inline void setup_signal_handlers()
    {
        signal(SIGINT, stop_handler);
        signal(SIGTERM, stop_handler);
    }


    enum class ParseReturn {
        ok,
        failure,
        exit
    };

    struct ApplicationArguments {
        ParseReturn parse_result;
        unsigned int domain_id;
        std::string this_station_name;
        uint32_t data_sample_size;
        std::string from_station_name;
        bool is_vid_pub;
        std::string qos_profile;
        rti::config::Verbosity verbosity;

        ApplicationArguments(
            ParseReturn parse_result_param,
            unsigned int domain_id_param,
            std::string this_station_name_param,
            uint32_t data_sample_size_param,
            std::string from_station_name_param,
            bool is_vid_pub_param,
            std::string qos_profile_param,
            rti::config::Verbosity verbosity_param)
            : parse_result(parse_result_param),
            domain_id(domain_id_param),
            this_station_name(this_station_name_param),
            data_sample_size(data_sample_size_param),
            from_station_name(from_station_name_param),
            is_vid_pub(is_vid_pub_param),
            qos_profile(qos_profile_param),
            verbosity(verbosity_param) {}
    };

    inline void set_verbosity(
        rti::config::Verbosity& verbosity,
        int verbosity_value)
    {
        switch (verbosity_value) {
        case 0:
            verbosity = rti::config::Verbosity::SILENT;
            break;
        case 1:
            verbosity = rti::config::Verbosity::EXCEPTION;
            break;
        case 2:
            verbosity = rti::config::Verbosity::WARNING;
            break;
        case 3:
            verbosity = rti::config::Verbosity::STATUS_ALL;
            break;
        default:
            verbosity = rti::config::Verbosity::EXCEPTION;
            break;
        }
    }

    /** ------------------------------------------------------------
     * parse_arguments()
     * Parse the command line arguments, returning a struct.
     * This also works with a configuration file for convenience.
     * CmdLine args have priority over config file content.
     **/
    inline ApplicationArguments parse_arguments(int argc, char *argv[])
    {
        int arg_processing = 1;
        bool show_usage = false;
        ParseReturn parse_result = ParseReturn::ok;

        // arg priority is: 1:cmdLine args, 2:args from config file, 3: defaults
        // 3: init with defaults
        unsigned int domain_id = 0;
        std::string this_station_name = "MyLocalStation";    // my station name 
        std::string from_station_name = "FarEndStation";     // far-end station name
        std::string config_filename = config_filename_default;
        bool is_vid_pub = false;
        bool writeback_config_file = false;
        std::string qos_profile = "b";
        uint32_t data_sample_size = 1316;
        rti::config::Verbosity verbosity(rti::config::Verbosity::EXCEPTION);

        // 2: parms from config file.  Was one specified as cmdline arg?
        while (arg_processing < argc) {
            if ((argc > arg_processing + 1)
            && (strcmp(argv[arg_processing], "-c") == 0
            || strcmp(argv[arg_processing], "--configfile") == 0)) {
                config_filename = std::string(argv[arg_processing + 1]);
                arg_processing = argc;
            }
            else {
                arg_processing += 1;
            }
        }

        // load properties from file
        PropertyUtil* prop = new PropertyUtil(config_filename);
        domain_id = prop->getIntProperty("config.domainId");
        uint32_t tmp_sample_size = prop->getIntProperty("config.data_sample_size");
        if(tmp_sample_size != 0) data_sample_size = tmp_sample_size;
        std::string tmp_str = prop->getStringProperty("config.this_station_name");
        if(tmp_str != "") this_station_name = tmp_str;
        tmp_str = prop->getStringProperty("config.from_station_name");
        if(tmp_str != "") from_station_name = tmp_str;
        tmp_str = prop->getStringProperty("config.qos_profile");
        if (tmp_str != "") qos_profile = tmp_str;

        // 1: parse the command line args
        arg_processing = 1;
        while (arg_processing < argc) {
            if ((argc > arg_processing + 1)
                && (strcmp(argv[arg_processing], "-d") == 0
                    || strcmp(argv[arg_processing], "--domain") == 0)) {
                domain_id = atoi(argv[arg_processing + 1]);
                arg_processing += 2;
            }
            else if ((argc > arg_processing + 1)
                && (strcmp(argv[arg_processing], "-b") == 0
                    || strcmp(argv[arg_processing], "--buffer") == 0)) {
                data_sample_size = atoi(argv[arg_processing + 1]);
                arg_processing += 2;
            }
            else if ((argc > arg_processing + 1)
                && (strcmp(argv[arg_processing], "-c") == 0
                    || strcmp(argv[arg_processing], "--configfile") == 0)) {
                config_filename = std::string(argv[arg_processing + 1]);
                arg_processing += 2;
            }
            else if ((strcmp(argv[arg_processing], "-p") == 0
                || strcmp(argv[arg_processing], "--pub") == 0)) {
                this_station_name = std::string(argv[arg_processing + 1]);
                is_vid_pub = true;
                arg_processing += 2;
            }
            else if ((strcmp(argv[arg_processing], "-s") == 0
                || strcmp(argv[arg_processing], "--sub") == 0)) {
                from_station_name = std::string(argv[arg_processing + 1]);
                is_vid_pub = false;
                arg_processing += 2;
            }
            else if ((strcmp(argv[arg_processing], "-w") == 0
                || strcmp(argv[arg_processing], "--writeback") == 0)) {
                writeback_config_file = true;
                arg_processing += 1;
            }
            else if ((argc > arg_processing + 1)
                && (strcmp(argv[arg_processing], "-q") == 0
                    || strcmp(argv[arg_processing], "--qos") == 0)) {
                qos_profile = std::string(argv[arg_processing + 1]);
                arg_processing += 2;
            }
            else if ((argc > arg_processing + 1)
                && (strcmp(argv[arg_processing], "-v") == 0
                    || strcmp(argv[arg_processing], "--verbosity") == 0)) {
                set_verbosity(verbosity, atoi(argv[arg_processing + 1]));
                arg_processing += 2;
            }
            else if (strcmp(argv[arg_processing], "-h") == 0
                || strcmp(argv[arg_processing], "--help") == 0) {
                std::cout << "Example application." << std::endl;
                show_usage = true;
                parse_result = ParseReturn::exit;
                break;
            }
            else {
                std::cout << "Bad parameter." << std::endl;
                show_usage = true;
                parse_result = ParseReturn::failure;
                break;
            }
        }

        if (show_usage) {
            std::cout << "Usage:\n"\
                "    -d, --domain      <int>     Domain ID this application will operate in\n" \
                "                                Default: " << domain_id << "\n"\
                "    -p, --pub         <string>  Publish (video stream) as this ID\n"\
                "    -s, --sub         <string>  Subscribe (video stream) from this ID\n"\
                "    -b, --buffer      <int>     Size of the data buffer (DDS sample size) in bytes\n"\
                "                                 Default: " << data_sample_size << "\n"\
                "    -c, --configfile  <string>  Configuration filename to load\n"\
                "                                 Default: " << config_filename_default << "\n"\
                "    -w, --writeback             Write-back to the config file, updated args\n"\
                "                                \n"\
                "    -q, --qos         <a,b,c>   QoS profile to use: a:reliable, b:best-effort,\n"\
                "                                 c:user-defined.  All are in USER_QOS_PROFILES.xml\n"\
                "                                 Default: " << qos_profile << "\n"\
                "    -v, --verbosity   <int>     How much debugging output to show.\n"\
                "                                 Range: 0-3 \n"\
                "                                 Default: 1 (EXCEPTION)\n"\
                "    -h, --help                  Print this list and exit\n"\
                << std::endl;
        }

        // write-back the config file if asked
        if(writeback_config_file) {
            std::map<const std::string, std::string> tmpMap = prop->getPropertyMap();
            tmpMap["config.data_sample_size"] = std::to_string(data_sample_size);
            tmpMap["config.domainId"] = std::to_string(domain_id);
            tmpMap["config.from_station_name"] = this_station_name;
            tmpMap["config.this_station_name"] = from_station_name;
            tmpMap["config.qos_profile"] = qos_profile;
            std::ofstream fout(config_filename);
            if(fout) {
                for (auto kv : tmpMap) {
                    fout << kv.first << "=" << kv.second << std::endl;
                }
            }
            else {
                std::cerr << "Write-back failure to file " << config_filename << std::endl;
            }

        }

        return ApplicationArguments(
            parse_result, domain_id, this_station_name, data_sample_size, from_station_name, 
            is_vid_pub, qos_profile, verbosity);
 
    }

    /** ----------------------------------------------------------------
     * contact_name_to_id()
     * create a hash of the name, convert to BASE64 and produce an ID
     * composed of: [first 1-3 chars of name][5-7 chars of BASE64 hash (30 bit equiv)]
     * This is done to make a consistent size, human-readable ID from the name string.
     **/
    inline void contact_name_to_id(std::string name, std::string& id)
    {
        // get a hash of the name string, convert to BASE64 string
        uint64_t nameHash[2];
        uint32_t hashSeed = 0x0ec3d821;   // no significance to this number, other that it is prime
        MurmurHash3_x64_128(name.c_str(), (int)name.size(), hashSeed, &nameHash);

        char b64[9];
        for (int i = 0; i < 8; i++) {
            if ((nameHash[0] & 0x3f) < 26) { b64[i] = 'A' + (nameHash[0] & 0x3f); }
            else if ((nameHash[0] & 0x3f) < 52) { b64[i] = 'a' + ((nameHash[0] & 0x3f) - 26); }
            else if ((nameHash[0] & 0x3f) < 62) { b64[i] = '0' + ((nameHash[0] & 0x3f) - 52); }
            else if ((nameHash[0] & 0x3f) == 62) { b64[i] = '+'; }
            else { b64[i] = '/'; }
            nameHash[0] = (nameHash[0] >> 6) | ((nameHash[1] & 0x3f) << 58);
            nameHash[1] = nameHash[1] >> 6;
        }
        b64[8] = 0;

        // now construct the ID from: [first 1-3 chars of name : 7-5 char BASE64 hash] = 8-char total
        size_t nameLen = name.size();
        if (nameLen > 3) nameLen = 3;
        size_t b64Len = 8 - nameLen;
        int i = 0;
        while (nameLen--) {
            id.push_back(name.at(i++));
        }
        while (b64Len--) {
            id.push_back(b64[i++]);
        }
    }


}  // namespace application

#endif  // __APP_HELPER_HPP__