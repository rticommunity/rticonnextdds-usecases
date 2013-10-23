/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#include "EnumPrintHelpers.h"

using namespace com::rti::chocolatefactory::generated;


// TODO comment this
void StationControllerType::GetControllerPrettyName(
		com::rti::chocolatefactory::generated::StationControllerKind kind,
		std::string &kindOut)
{
	if (kind == SUGAR_CONTROLLER)
	{
		kindOut = "Sugar Controller";
	}
	else if (kind == COCOA_BUTTER_CONTROLLER)
	{
		kindOut = "Cocoa Butter Controller";
	}
	else if (kind == COCOA_LIQUOR_CONTROLLER)
	{
		kindOut = "Cocoa Liquor Controller";
	}
	else if (kind == VANILLA_CONTROLLER)
	{
		kindOut = "Vanilla Controller";
	}
	else if (kind == MILK_CONTROLLER)
	{
		kindOut = "Milk Controller";
	}

}

// TODO: Comment this
void StationControllerType::GetControllerEnumName(
		com::rti::chocolatefactory::generated::StationControllerKind kind,
		std::string &kindOut)
{
	if (kind == SUGAR_CONTROLLER)
	{
		kindOut = "'SUGAR_CONTROLLER'";
	}
	else if (kind == COCOA_BUTTER_CONTROLLER)
	{
		kindOut = "'COCOA_BUTTER_CONTROLLER'";
	}
	else if (kind == COCOA_LIQUOR_CONTROLLER)
	{
		kindOut = "'COCOA_LIQUOR_CONTROLLER'";
	}
	else if (kind == VANILLA_CONTROLLER)
	{
		kindOut = "'VANILLA_CONTROLLER'";
	}
	else if (kind == MILK_CONTROLLER)
	{
		kindOut = "'MILK_CONTROLLER'";
	}

}

void LotStatusType:: GetLotStatusPrettyName(
		com::rti::chocolatefactory::generated::LotStatusKind kind,
		std::string &kindOut)
{
	if (kind == ASSIGNED_TO_SC)
	{
		kindOut = "Assigned to Station Controller";
	}
	else if (kind == WAITING_AT_SC)
	{
		kindOut = "Waiting at Station Controller";
	}
	else if (kind == PROCESSING_AT_SC)
	{
		kindOut = "Processing at Station Controller";
	}
	else if (kind == COMPLETED)
	{
		kindOut = "Completed";
	}
}


