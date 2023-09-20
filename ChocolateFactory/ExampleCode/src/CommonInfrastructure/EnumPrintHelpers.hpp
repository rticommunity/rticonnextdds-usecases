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

/* EnumPrintHelpers.h

A set of functions that assist in the conversion of Enumerated values defined
in the IDL from integer enums to strings.

*/
#ifndef ENUM_PRINT_HELPERS_H
#define ENUM_PRINT_HELPERS_H

#include <string>
#include "../Generated/ChocolateFactory.hpp"

using namespace com::chocolatefactory::generated;

// ------------------------------------------------------------------------- //
//
// StationControllerType:
// A small helper class that converts between the enumeration type and a
// pretty name for printing or a string that represents the enumeration for
// content-filtering purposes.
//
class StationControllerType {
public:
    // --- Static methods ---

    // Converts from a StationControllerKind to a nice readable name for
    // printing messages
    static std::string ControllerPrettyName(StationControllerKind kind);

    // Converts from a StationControllerKind to a string that represents
    // the enumeration
    static std::string ControllerEnumName(StationControllerKind kind);

    // Takes a StationControllerKind and fills in a string that represents
    // the type of ingredient that controller adds
    static std::string ControllerIngredientName(
            com::chocolatefactory::generated::StationControllerKind kind);
};

class LotStatusType {
public:
    // --- Static methods ---

    // Converts from a LotStatusKind to a nice readable name for
    // printing messages
    static std::string LotStatusPrettyName(
            com::chocolatefactory::generated::LotStatusKind kind);
};

#endif
