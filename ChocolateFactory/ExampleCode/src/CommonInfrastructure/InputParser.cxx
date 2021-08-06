/*
 * (c) 2021 Copyright, Real-Time Innovations, Inc. (RTI) All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the software solely for use with RTI Connext DDS.  Licensee may
 * redistribute copies of the software provided that all such copies are
 * subject to this license. The software is provided "as is", with no warranty
 * of any type, including any warranty for fitness for any purpose. RTI is
 * under no obligation to maintain or support the software.  RTI shall not be
 * liable for any incidental or consequential damages arising out of the use or
 * inability to use the software.
 */

#include "InputParser.hpp"

InputParser::InputParser(int& argc, char* argv[]) {
    for (int i = 1; i < argc; ++i)
        tokens.push_back(std::string(argv[i]));
}

const std::string& InputParser::getCmdOption(const std::string& option) const {
    std::vector<std::string>::const_iterator itr;
    itr = std::find(tokens.begin(), tokens.end(), option);
    if (itr != tokens.end() && ++itr != tokens.end()) {
        return *itr;
    }
    else {
        static const std::string empty_string("");
        return empty_string;
    }
}

bool InputParser::cmdOptionExists(const std::string& option) const {
    return std::find(tokens.begin(), tokens.end(), option) != tokens.end();
}