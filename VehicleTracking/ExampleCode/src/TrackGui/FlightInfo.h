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
