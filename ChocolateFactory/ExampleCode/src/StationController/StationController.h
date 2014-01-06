/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#ifndef STATION_CONTROLLER_H
#define STATION_CONTROLLER_H

#include "StationControllerInterface.h"
#include "../Generated/ChocolateFactory.h"

class StationController
{

public:
	// --- Constructor --- 
	StationController(
		com::rti::chocolatefactory::generated::StationControllerKind kind,
		StationControllerInterface *scInterface);
	
	// --- Process lots --- 
	void ProcessLots();

	// --- Update lot state --- 
	void UpdateState(
		DdsAutoType<com::rti::chocolatefactory::generated::ChocolateLotState> 
			*updatedState);
	
	// --- Process lot --- 
	void ProcessLot(
		DdsAutoType<com::rti::chocolatefactory::generated::ChocolateLotState> 
			*lotState);

private:

	// --- Private members --- 
	StationControllerInterface *_networkInterface;
	bool _shuttingDown;
	com::rti::chocolatefactory::generated::StationControllerKind 
			_stationControllerKind;
};

#endif