/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#ifndef ENUM_PRINT_HELPERS_H
#define ENUM_PRINT_HELPERS_H

#include <string>
#include "../Generated/ChocolateFactory.h"

// ------------------------------------------------------------------------- //
//
// StationControllerType:
// A small helper class that converts between the enumeration type and a 
// pretty name for printing or a string that represents the enumeration for
// content-filtering purposes.	
//
class StationControllerType
{
public:

	// --- Static methods --- 

	// Converts from a StationControllerKind to a nice readable name for
	// printing messages
	static void GetControllerPrettyName(
		com::rti::chocolatefactory::generated::StationControllerKind kind,
		std::string &kindOut);

	// Converts from a StationControllerKind to a string that represents
	// the enumeration
	static void GetControllerEnumName(
		com::rti::chocolatefactory::generated::StationControllerKind kind,
		std::string &kindOut);

	// Takes a StationControllerKind and fills in a string that represents
	// the type of ingredient that controller adds	
	static void GetControllerIngredientName(
		com::rti::chocolatefactory::generated::StationControllerKind kind,
		std::string &ingredientOut);


};

class LotStatusType
{
public:

	// --- Static methods --- 

	// Converts from a LotStatusKind to a nice readable name for
	// printing messages
	static void GetLotStatusPrettyName(
		com::rti::chocolatefactory::generated::LotStatusKind kind,
		std::string &kindOut);

};

#endif
