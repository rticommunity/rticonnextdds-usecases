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


// ------------------------------------------------------------------------- //
// Converts from a StationControllerKind to a string representation of what
// the Station Controller does
void StationControllerType::GetControllerPrettyName(
		StationControllerKind kind,
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

// ------------------------------------------------------------------------- //
// Converts from a StationControllerKind to a string representation of the
// enumeration kind
void StationControllerType::GetControllerEnumName(
		StationControllerKind kind,
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


// ------------------------------------------------------------------------- //
// Converts from a StationControllerKind to a string representation of the
// ingredient that the Station Controller adds to the recipe
void StationControllerType::GetControllerIngredientName(
		StationControllerKind kind,
		std::string &ingredientOut)
{
	if (kind == SUGAR_CONTROLLER)
	{
		ingredientOut = "sugar";
	}
	else if (kind == COCOA_BUTTER_CONTROLLER)
	{
		ingredientOut = "cocoa butter";
	}
	else if (kind == COCOA_LIQUOR_CONTROLLER)
	{
		ingredientOut = "cocoa liquor";
	}
	else if (kind == VANILLA_CONTROLLER)
	{
		ingredientOut = "vanilla";
	}
	else if (kind == MILK_CONTROLLER)
	{
		ingredientOut = "milk";
	}


}

void LotStatusType:: GetLotStatusPrettyName(
		LotStatusKind kind,
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
	else if (kind == LOT_COMPLETED)
	{
		kindOut = "Lot Completed";
	}
}


