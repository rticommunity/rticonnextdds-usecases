/*******************************************************************************
 (c) 2005-2014 Copyright, Real-Time Innovations, Inc.  All rights reserved.
 RTI grants Licensee a license to use, modify, compile, and create derivative
 works of the Software.  Licensee has the right to distribute object form only
 for use with RTI products.  The Software is provided "as is", with no warranty
 of any type, including any warranty for fitness for any purpose. RTI is under
 no obligation to maintain or support the Software.  RTI shall not be liable for
 any incidental or consequential damages arising out of the use or inability to
 use the software.
 ******************************************************************************/
#ifndef FLIGHT_INFO_H
#define FLIGHT_INFO_H

#include "wx/setup.h"
#include "../Generated/AirTrafficControl.h"
#include "../CommonInfrastructure/DDSTypeWrapper.h"


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
struct FlightInfo
{
	DdsAutoType<com::rti::atc::generated::Track> _track;
	DdsAutoType<com::rti::atc::generated::FlightPlan> _plan;

};

#endif
