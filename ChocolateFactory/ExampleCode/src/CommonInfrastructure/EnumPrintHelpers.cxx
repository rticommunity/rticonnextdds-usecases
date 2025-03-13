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

/* EnumPrintHelpers.cxx

   A set of functions that assist in the conversion of Enumerated values defined
   in the IDL from integer enums to strings.

*/
#include "EnumPrintHelpers.hpp"

using namespace com::chocolatefactory::generated;


// ------------------------------------------------------------------------- //
// Converts from a StationControllerKind to a string representation of what
// the Station Controller does
std::string StationControllerType::ControllerPrettyName(StationControllerKind kind)
{
    if (kind == StationControllerKind::SUGAR_CONTROLLER) {
        return std::string("Sugar Controller");
    } else if (kind == StationControllerKind::COCOA_BUTTER_CONTROLLER) {
        return std::string("Cocoa Butter Controller");
    } else if (kind == StationControllerKind::COCOA_LIQUOR_CONTROLLER) {
        return std::string("Cocoa Liquor Controller");
    } else if (kind == StationControllerKind::VANILLA_CONTROLLER) {
        return std::string("Vanilla Controller");
    } else if (kind == StationControllerKind::MILK_CONTROLLER) {
        return std::string("Milk Controller");
    }
}

// ------------------------------------------------------------------------- //
// Converts from a StationControllerKind to a string representation of the
// enumeration kind
std::string StationControllerType::ControllerEnumName(StationControllerKind kind)
{
    if (kind == StationControllerKind::SUGAR_CONTROLLER) {
        return std::string("'SUGAR_CONTROLLER'");
    } else if (kind == StationControllerKind::COCOA_BUTTER_CONTROLLER) {
        return std::string("'COCOA_BUTTER_CONTROLLER'");
    } else if (kind == StationControllerKind::COCOA_LIQUOR_CONTROLLER) {
        return std::string("'COCOA_LIQUOR_CONTROLLER'");
    } else if (kind == StationControllerKind::VANILLA_CONTROLLER) {
        return std::string("'VANILLA_CONTROLLER'");
    } else if (kind == StationControllerKind::MILK_CONTROLLER) {
        return std::string("'MILK_CONTROLLER'");
    }
}


// ------------------------------------------------------------------------- //
// Converts from a StationControllerKind to a string representation of the
// ingredient that the Station Controller adds to the recipe
std::string StationControllerType::ControllerIngredientName(StationControllerKind kind)
{
    if (kind == StationControllerKind::SUGAR_CONTROLLER) {
        return std::string("sugar");
    } else if (kind == StationControllerKind::COCOA_BUTTER_CONTROLLER) {
        return std::string("cocoa butter");
    } else if (kind == StationControllerKind::COCOA_LIQUOR_CONTROLLER) {
        return std::string("cocoa liquor");
    } else if (kind == StationControllerKind::VANILLA_CONTROLLER) {
        return std::string("vanilla");
    } else if (kind == StationControllerKind::MILK_CONTROLLER) {
        return std::string("milk");
    }
}

std::string LotStatusType::LotStatusPrettyName(LotStatusKind kind)
{
    if (kind == LotStatusKind::ASSIGNED_TO_SC) {
        return std::string("Assigned to Station Controller");
    } else if (kind == LotStatusKind::WAITING_AT_SC) {
        return std::string("Waiting at Station Controller");
    } else if (kind == LotStatusKind::PROCESSING_AT_SC) {
        return std::string("Processing at Station Controller");
    } else if (kind == LotStatusKind::LOT_COMPLETED) {
        return std::string("Lot Completed");
    }
}
