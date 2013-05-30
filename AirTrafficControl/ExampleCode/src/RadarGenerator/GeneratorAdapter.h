#ifndef GENERATOR_ADAPTER_H
#define GENERATOR_ADAPTER_H

#include "../CommonInfrastructure/DDSTypeWrapper.h"
#include "../Generated/AirTrafficControl.h"
#include "TrackGenerator.h"
#include "RadarInterface.h"

// ------------------------------------------------------------------------- //
//
// DGenerator Adapter:
// This class converts between the data types of the "generator" and the 
// network.  This is a typical pattern - that you will need to adapt between
// your application's data types and the data types that are sent over the 
// network.
//
// ------------------------------------------------------------------------- //




// Common pattern for converting between internal "radar" data types and
// network data types.  In other words, this converts between GeneratorTrack
// and GeneratorFlightPlan to Track and FlightPlan data types.

class RadarAdapter {
public:
	static void AdaptToGeneratorTrack(GeneratorTrack &genTrack, 
		const DdsAutoType<com::rti::atc::generated::Track> &track) {
		genTrack.altitudeInFeet = track.altitude;
		genTrack.latLong.latitude = track.latitude;
		genTrack.latLong.longitude = track.longitude;
		genTrack.id = track.trackId;		
		genTrack.SetFlightId(track.flightId);

	}

	static void AdaptToTrack(
		DdsAutoType<com::rti::atc::generated::Track> &track, 
		const GeneratorTrack &genTrack) {
		track.altitude = genTrack.altitudeInFeet;
		track.latitude = genTrack.latLong.latitude;
		track.longitude = genTrack.latLong.longitude;
		track.trackId = genTrack.id;
		sprintf(track.flightId, genTrack.GetFlightId());
	}

	static void AdaptToGeneratorFlightPlan(GeneratorFlightPlan &genPlan, 
		const com::rti::atc::generated::FlightPlan &plan) {
		genPlan.estimatedHours = plan.estimatedHours;
		genPlan.estimatedMinute = plan.estimatedMinutes;
		sprintf(genPlan.flightID, "%s", plan.flightId);
	}

	static void AdaptToFlightPlan(
		com::rti::atc::generated::FlightPlan &plan, 
		const GeneratorFlightPlan &genPlan) {
		plan.estimatedHours = genPlan.estimatedHours;
		plan.estimatedMinutes = genPlan.estimatedMinute;
		sprintf(plan.flightId, genPlan.flightID);
	}

};

#endif