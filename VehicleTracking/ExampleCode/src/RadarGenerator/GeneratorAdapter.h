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

#ifndef GENERATOR_ADAPTER_H
#define GENERATOR_ADAPTER_H

#include "../Generated/AirTrafficControl.hpp"
#include "TrackGenerator.h"
#include "RadarInterface.h"

// ------------------------------------------------------------------------- //
//
// Generator Adapter:
// This class converts between the data types of the "generator" and the
// network.  This is a typical pattern - that you will need to adapt between
// your application's data types and the data types that are sent over the
// network.
//
// ------------------------------------------------------------------------- //

class RadarAdapter {
public:
    // --- Adapting types ---
    // Common pattern for converting between internal "radar" data types and
    // network data types.  In other words, this converts between GeneratorTrack
    // and GeneratorFlightPlan to Track and FlightPlan data types.
    static void AdaptToGeneratorTrack(
            GeneratorTrack& genTrack,
            const com::atc::generated::Track& track)
    {
        genTrack.altitudeInFeet = track.altitude();
        genTrack.latLong.latitude = track.latitude();
        genTrack.latLong.longitude = track.longitude();
        genTrack.id = track.trackId();
        genTrack.SetFlightId(track.flightId());
    }

    // --- Adapting types ---
    // Common pattern for converting between internal "radar" data types and
    // network data types.  In other words, this converts between GeneratorTrack
    // and GeneratorFlightPlan to Track and FlightPlan data types.
    static void AdaptToTrack(
            com::atc::generated::Track& track,
            const GeneratorTrack& genTrack)
    {
        track.altitude(genTrack.altitudeInFeet);
        track.latitude(genTrack.latLong.latitude);
        track.longitude(genTrack.latLong.longitude);
        track.trackId(genTrack.id);
        track.flightId(genTrack.GetFlightId());
    }

    // --- Adapting types ---
    // Common pattern for converting between internal "radar" data types and
    // network data types.  In other words, this converts between GeneratorTrack
    // and GeneratorFlightPlan to Track and FlightPlan data types.
    static void AdaptToGeneratorFlightPlan(
            GeneratorFlightPlan& genPlan,
            const com::atc::generated::FlightPlan& plan)
    {
        genPlan.estimatedHours = plan.estimatedHours();
        genPlan.estimatedMinute = plan.estimatedMinutes();
        sprintf(genPlan.flightID, "%s", plan.flightId().c_str());
    }

    // --- Adapting types ---
    // Common pattern for converting between internal "radar" data types and
    // network data types.  In other words, this converts between GeneratorTrack
    // and GeneratorFlightPlan to Track and FlightPlan data types.
    static void AdaptToFlightPlan(
            com::atc::generated::FlightPlan& plan,
            const GeneratorFlightPlan& genPlan)
    {
        plan.estimatedHours(genPlan.estimatedHours);
        plan.estimatedMinutes(genPlan.estimatedMinute);
        plan.flightId(genPlan.flightID);
    }
};

#endif
