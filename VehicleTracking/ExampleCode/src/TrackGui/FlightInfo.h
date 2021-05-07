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

#ifndef FLIGHT_INFO_H
#define FLIGHT_INFO_H

#include "wx/setup.h"
#include "../Generated/AirTrafficControl.hpp"

// ------------------------------------------------------------------------- //
//
// FlightInfo:
// This type represents all the information available about a particular
// flight, including current track position and flight plan.
//
// In this example using the data types generated as a part of the network
// infrastructure.  It is just as likely that this would be a data type created
// by the application that represents the applications model of a flight type.
//
// ------------------------------------------------------------------------- //
struct FlightInfo {
    com::atc::generated::Track _track;
    com::atc::generated::FlightPlan _plan;
};

#endif
