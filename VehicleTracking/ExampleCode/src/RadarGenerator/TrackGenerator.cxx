/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#include <math.h>
#include <sstream>
#include <iostream>
#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"
#include "../CommonInfrastructure/OSAPI.h"
#include "TrackGenerator.h"


// ------------------------------------------------------------------------- //
// 
// Note that this file generates interesting-looking data, but this is not the
// core value that RTI Connext DDS provides, which is the efficient transport
// of data over one or more transports to all interested parties.  
//
// None of this is required to send data over DDS!  This is simply a data 
// source that is sending radar data.
//
// This class generates example track data that is sent to illustrate how RTI
// can send track data over DDS.  This example data is not intended to be 
// complete or accurate, and there may be errors in the generated data.  This  
// roughly simulates an air traffic control radar that can detect aircraft 
// flying within 80 Km of SFO, using some of the typical flight paths.

// It does not include radar tracks of aircraft landing at other nearby 
// airports, and it does not prevent (or accurately simulate) collisions of 
// aircraft.  Note that this example currently does not set the altitude, 
// though we may add that in the future.
//
// ------------------------------------------------------------------------- //

// Pre-defined lat/longs where the flight paths may go.  These are all rough
// estimates except for the position of SFO.

// SFO's position
#define SFO_LAT                37.619
#define SFO_LONG               -122.3749

// Planes arriving from the north will approach from here
#define APPROACH_BEGIN_LAT 37.5586
#define APPROACH_BEGIN_LONG -122.2700

// Defines to help generate semi-accurate positional information about
// aircraft.
#define SEC_PER_HOUR (60 * 60)
#define MILLISEC_PER_SEC 1000
#define M_PI                   3.14159265358979323846

#define EARTH_MEAN_RADIUS_KM 6371


// ------------------------------------------------------------------------- //
// Destructor for the track generator. Deletes all listeners, 
// all tracks, and all flight plans
TrackGenerator::~TrackGenerator()
{
	_mutex->Lock();

	// Remove all listeners
	for (std::vector<TrackListener *>::iterator it = _listeners.begin(); 
			it != _listeners.end(); ++it) 
	{
		delete (*it);
	}
	_listeners.clear();

	// If I have been storing flightplan data, remove it
	while(!_flightPlans.empty()) 
	{
		GeneratorFlightPlan *plan = _flightPlans.front();
		delete plan;
		_flightPlans.pop();
	}

	// Remove all tracks I have generated
	for (std::vector<GeneratorTrack *>::iterator it = _trackList.begin(); 
			it != _trackList.end(); ++it) 
	{
		delete (*it);
	}
	_trackList.clear();

	_mutex->Unlock();

	delete _mutex;
}

// ------------------------------------------------------------------------- //
// Removes a listener from the generator.  The listeners receive updates about
// the tracks, and can do whatever is necessary when a track is updated.
void TrackGenerator::RemoveListener(const TrackListener *listener)
{

	// Locks the mutex in case this is in process of updating
	// a track at the same time the listener is being removed.
	_mutex->Lock();

	std::vector<TrackListener *>::iterator toErase;
	
	// Search for listener to remove
	for(std::vector<TrackListener *>::iterator it = 
		_listeners.begin(); it != _listeners.end(); 
		++it)
	{
		if ((*it) == listener)
		{
			toErase = it;
		}
	}

	_listeners.erase(toErase);

	_mutex->Unlock();

}

// ------------------------------------------------------------------------- //
// Using an observer pattern to notify observers that a track has been deleted.
void TrackGenerator::NotifyListenersDeleteTrack(const GeneratorTrack &track)
{
	_mutex->Lock();

	for (std::vector<TrackListener *>::iterator it = _listeners.begin(); 
		it != _listeners.end(); ++it) 
	{
		if (false == (*it)->TrackDelete(track)) 
		{
			std::stringstream errss;
			errss << "NotifyListenersDeleteTrack(): error deleting track.";
			throw errss.str();
		}
	}

	_mutex->Unlock();
}

// ------------------------------------------------------------------------- //
// Using an observer pattern to notify observers that a track has been updated.
void TrackGenerator::NotifyListenersUpdateTrack(const GeneratorTrack &track)
{
	_mutex->Lock();

	for (std::vector<TrackListener *>::iterator it = _listeners.begin();
		it != _listeners.end(); ++it) 
	{

		if (false == (*it)->TrackUpdate(track)) 
		{
			std::stringstream errss;
			errss << "NotifyListenersUpdateTrack(): error updating track.";
			throw errss.str();

		}
	}

	_mutex->Unlock();

}

// ------------------------------------------------------------------------- //
// Function that is called by the generator's thread, and calls the 
// generator method that periodically generates tracks.
void *TrackGenerator::GenerateTracksFunc(void *arg) 
{
	TrackGenerator *gen = (TrackGenerator *)arg;

	try 
	{
		gen->GenerateTracks();
	}
	catch (std::string message)
	{
		std::cout << "Application exception: " << message << std::endl;
	}

    return NULL;
}


// Creates a track in the TrackGenerator.  Note that this recycles track IDs over time.
// Called from spawned TrackGenerator thread
GeneratorTrack* TrackGenerator::AddTrack(bool randomLocation)
{

	// Cannot create more tracks than the generator is 
	// supposed to handle
	if (_trackList.size() == _maxTracks) 
	{
		return NULL;
	}

	GeneratorTrack *track = new GeneratorTrack(_mutex);

	// Recycle track ID when it gets to the max
	if (_currentTrackId == GetMaxTracks()) 
	{
		_currentTrackId = 0;
	}
	track->id = _currentTrackId;

	CalculateRandomPoint80KmFromSFO(&track->latLong, randomLocation);
	if (!_flightPlans.empty()) 
	{

		GeneratorFlightPlan *plan = _flightPlans.front();

		// This is pretty much a dummy call here, because this example does not
		// actually do real correlation - instead it simply checks if the track
		// has an empty flight ID, and considers the flight plan to be 
		// "correlated" when the track has no flight ID.  However, this logic
		// is here to represent a real application.
		if (CorrelateFlightPlanWithTrack(plan, track))
		{

			// Copies data from the flight plan, does not keep a reference to 
			// the flight plan
			UpdateTrackWithFlightData(*track, *plan);

			// No longer need to store the flight plan since the required data
			// is now stored with the track.
			delete plan;
			_flightPlans.pop();
		}
	}

	_currentTrackId++;
	_trackList.push_back(track);

	return track;
}


// ------------------------------------------------------------------------- //
// Copies data from the flight plan, does not keep a reference to the flight
// plan
void TrackGenerator::UpdateTrackWithFlightData(GeneratorTrack &track, 
	GeneratorFlightPlan &flightPlan)
{
	// Copies the flight ID - no need to worry about allocation of the
	// flight ID string.
	track.SetFlightId(flightPlan.flightID);
}

// Deletes the track from the list. 
void TrackGenerator::DeleteTrack(GeneratorTrack &track)
{
	for (std::vector<GeneratorTrack *>::iterator it = 
			_trackList.begin(); 	
			it != _trackList.end(); ++it) 
	{
		if ((*it)->id == track.id) 
		{
			_trackList.erase(it);
			break;
		}
	}
}

// ------------------------------------------------------------------------- //
// Creates and starts a thread that starts "generating track data"
void TrackGenerator::Start()
{
	// The Radar has a thread that generates fake tracks
	OSThread *thread = new OSThread(
		(ThreadFunction)GenerateTracksFunc, this);
	thread->Run();
}

// ------------------------------------------------------------------------- //
// Marks itself as shutting down so the thread will break after the next sleep
// time.
void TrackGenerator::Shutdown()
{
	_shuttingDown = true;
}


// ------------------------------------------------------------------------- //
// CorrelateFlightPlanWithTrack:
// We are not doing any actual correlation logic here - this is literally 
// checking that the track that does not have a flight ID set, and copying 
// the flight ID from the flight plan into the track.
//
// In a real application, this should be replaced with your own logic that 
// correlates a particular flight plan with a particular track.  
// ------------------------------------------------------------------------- //
bool TrackGenerator::CorrelateFlightPlanWithTrack(GeneratorFlightPlan *flightPlan, 
		GeneratorTrack *track)
{
	if (0 == strcmp(track->GetFlightId(), ""))
	{
		return true;
	}

	return false;
}

// ------------------------------------------------------------------------- //
// Either adds the flight plan's relevant information to the track, or stores 
// the flight plan until a new track is created later.
void TrackGenerator::AddFlightPlan(GeneratorFlightPlan *flightPlan)
{

	bool storeFlightPlan = true;

	// For all tracks, check if they are "correlated" with the new flight plan.
	// If yes, add the flight plan information to the track.  If no, store the
	// flight plan information.
	for (unsigned int i = 0; i < _trackList.size(); i++)
	{
		// This example does not actually do real correlation - instead it 
		// simply checks if the track has an empty flight ID, and considers the
		// flight plan to be "correlated" when the track has no flight ID.
		// However, this logic is here to represent a real application.
		if (CorrelateFlightPlanWithTrack(flightPlan, _trackList[i]))
		{
			UpdateTrackWithFlightData(*_trackList[i], *flightPlan);
			storeFlightPlan = false;
			break;
		}
	}

	if (storeFlightPlan)
	{
		// Only keep flight plans that will be associated with future tracks
		_flightPlans.push(new GeneratorFlightPlan(flightPlan));
	}
}

// ------------------------------------------------------------------------- //
// This generates tracks at a given rate that was specified in the startup
// parameters.
void TrackGenerator::GenerateTracks()
{
	DDS::Duration_t clockUpdatePeriod = {_sampleRateSec,_sampleRateNanosec};
	double timeToCreateTrack = 0;

	double sendRateSec = _sampleRateSec / _runRate;
	double sendRateNanosec = _sampleRateNanosec / _runRate;
	DDS::Duration_t actualSleepTime = {(long)sendRateSec,
		(unsigned long)sendRateNanosec};

	if (_startTracks > _maxTracks)
	{
			std::stringstream errss;
			errss << "Trying to create a generator with more starting tracks "
				<< "than the maximum number of tracks.";
			throw errss.str();
	}

	while (!IsShuttingDown())
	{

		double sampleRateInMs = clockUpdatePeriod.nanosec / 1000000;
		sampleRateInMs += 1000 * clockUpdatePeriod.sec;

		// If I need to create more tracks because either 1) I have just
		// started, and I must create the number requested for startup or, 
		// I am adding incremental tracks.
		if (GetActiveTrackNumber() < _startTracks )
		{
			// Add the track at a random location within the bounding circle
			AddTrack(true);
			timeToCreateTrack = 0;

		} else if ((timeToCreateTrack > _creationRateSec ) && 
			(GetActiveTrackNumber() < GetMaxTracks() ))
		{
			AddTrack(false);
			timeToCreateTrack = 0;
		}

		timeToCreateTrack++;


		for (int i = 0; i < GetActiveTrackNumber(); i++) 
		{
		
			GeneratorTrack *track = GetTrack(i);
			
			CalculatePathToSFO(&track->latLong, &track->bearing, 
				&track->state, sampleRateInMs);

			if (track->altitudeInFeet < 0) 
			{
				track->altitudeInFeet = 0;
			}

			// 3. Notify the listeners so they can do stuff with the track data
			if (track->state != LANDED)
			{
				NotifyListenersUpdateTrack(*track);
			} 
			else
			{
				NotifyListenersDeleteTrack(*track);
				DeleteTrack(*track);
			}


		}

		NDDSUtility::sleep(actualSleepTime);

    }

}



// ------------------------------------------------------------------------- //
// ------------------------------------------------------------------------- //
// 
//         NOTE: This code is purely to generate interesting-looking data.
// 
// Everything below this point is track generation code that is completely 
// irrelevant to the usage of RTI Connext DDS middleware.  This generates some 
// dummy data showing flights approaching SFO.
//
// ------------------------------------------------------------------------- //
// ------------------------------------------------------------------------- //

// Calculate the bearing of the aircraft, given its current location and the
// latitude and longitude that it is heading to.
void TrackGenerator::CalculateBearing(double *bearing, 
	LatLong initLatLong, 
	LatLong finalLatLong)
{
	double differenceLong = finalLatLong.longitude - initLatLong.longitude;

	double differenceLongInRads = differenceLong * M_PI / 180;
	double finalLatInRads = finalLatLong.latitude * M_PI / 180;
	double initLatInRads = initLatLong.latitude * M_PI / 180;

	double y = sin(differenceLongInRads) * cos(finalLatInRads);
	double x = cos(initLatInRads) * sin(finalLatInRads) - 
				sin(initLatInRads) * cos(finalLatInRads) 
					* cos(differenceLongInRads);

	// bearing is in rads here
	*bearing = atan2(y,x);

	// Back to degrees
	*bearing = *bearing / M_PI * 180;

	// Ensure this is between 0 and 360
	*bearing = fmod((*bearing + 360) , 360);
}

// Translate between knots and kilometers per hour
double TrackGenerator::KnotsToKph(double knots)
{
	return knots * 1.852;
}

// Forcing all flights to approach from the south, to look 
// interesting
void TrackGenerator::UpdateTrackPositionState(FlightState *state)
{
	if (*state == INITIAL) 
	{
		*state = ON_APPROACH;
		return;
	}
	if (*state == ON_APPROACH)
	{
		*state = LANDED;
		return;
	}
}

// Calculates the next latitude and longitude of the flight, given the
// lat/long, the bearing, the amount of time that has passed since the last 
// update.
void TrackGenerator::CalculateNextPosition(LatLong *latLong, double bearing, 
	double sampleMillisec, double speedInKnots)
{
	double kph = KnotsToKph(speedInKnots);
	double kpsec = kph / SEC_PER_HOUR;
	double kpmillisec = kpsec / MILLISEC_PER_SEC;

	double distanceMovedPerPeriod = sampleMillisec * kpmillisec;
	double distInRads = distanceMovedPerPeriod / EARTH_MEAN_RADIUS_KM;
	double latInRads = latLong->latitude * M_PI / 180;
	double longInRads = latLong->longitude * M_PI / 180;
	double bearingInRads = bearing * M_PI / 180;

	double newLat = asin ( sin(latInRads) * cos(distInRads) + 
		cos(latInRads) * sin(distInRads) * cos(bearingInRads));

	double newLong = longInRads + atan2(sin(bearingInRads) * 
		sin(distInRads) * cos(latInRads),
		cos(distInRads)- sin(latInRads) * sin (newLat));

	newLong = fmod((newLong+3 * M_PI), 2 * M_PI) - M_PI; 
	latLong->latitude = newLat / M_PI * 180;
	latLong->longitude = newLong / M_PI * 180;
}

// Each flight will start at some random point 80 Km from SFO.  This is 
// not the way that real flight traffic works, but it is good for an example of
// flights near SFO.
void TrackGenerator::CalculateRandomPoint80KmFromSFO(LatLong *latLong, 
	bool randomDistanceWithin)
{
	double randDegrees = rand() % 360;
	double randRads = randDegrees * M_PI / 180;
	double finalKm = 80;

	if (randomDistanceWithin)
	{
		finalKm = rand() % 80;
	}

	double latInRads = SFO_LAT * M_PI / 180;
	double longInRads = SFO_LONG * M_PI / 180;
	double distInRads = finalKm / EARTH_MEAN_RADIUS_KM;
	double bearing = randRads;

	double temp1 = sin(latInRads) * cos(distInRads);
	double temp2 = cos(latInRads) * sin(distInRads) * cos(bearing);
	double newLatInRads = 	asin (temp1 +  temp2);
	double newLongInRads =
		longInRads + atan2(sin(bearing)*sin(distInRads)*cos(latInRads),
					cos(distInRads) - (sin(latInRads) * sin(newLatInRads)));

	// Normalize to -180 - 180
	newLongInRads = fmod((newLongInRads + 3 * M_PI), (2 * M_PI)) - M_PI; 

	latLong->latitude = newLatInRads / M_PI * 180;
	latLong->longitude = newLongInRads / M_PI * 180;

	std::cout << "New aircraft being updated.  Lat, Long: " <<  
		latLong->latitude <<  latLong->longitude << std::endl;

}

// Fly to a particular position, and check if the flight may have passed the
// intended position.
void TrackGenerator::FlyToPosition(LatLong *latLong, double *bearing, 
						FlightState *state, double sampleMillisec, 
						LatLong endPositionLatLong,
						double speed)
{

	double currBearing = *bearing;
	LatLong current = *latLong;

	CalculateBearing(bearing, *latLong, endPositionLatLong);
	CalculateNextPosition(latLong, *bearing, 
		sampleMillisec, speed);

	// If we have passed the point
	if (PassedPoint(current, *latLong, 
		endPositionLatLong, *state)) 
	{
		*bearing = currBearing;
		UpdateTrackPositionState(state);
		return;
	}
}


// Flights go to a location southeast of SFO and then line up to
// land.  This does no checking to avoid collisions.
void TrackGenerator::CalculatePathToSFO(LatLong *currentLatLong, 
						double *bearing, FlightState *state, 
						double sampleRate)
{
	double approachBearing = 0; 
	LatLong approach;
	approach.latitude = APPROACH_BEGIN_LAT;
	approach.longitude = APPROACH_BEGIN_LONG;

	LatLong finalDestination;
	finalDestination.latitude = SFO_LAT;
	finalDestination.longitude = SFO_LONG;
	CalculateBearing(&approachBearing, approach, finalDestination);
	double turnRadius = 9.656;

	if (*state == INITIAL) 
	{
		// Make slightly dumb assumption that bearing is directly toward
		// SFO when flight is arriving in the airspace
		int speedInKnots = 220;

		CalculateBearing(bearing, *currentLatLong, finalDestination);
		LatLong approachLatLong;
		approachLatLong.latitude = APPROACH_BEGIN_LAT;
		approachLatLong.longitude = APPROACH_BEGIN_LONG;
		FlyToPosition(currentLatLong, bearing,
					state, sampleRate, 
					approachLatLong, speedInKnots);
	} 
	else if (*state == ON_APPROACH)
	{
		int speedInKnots = 140;
		FlyToPosition(currentLatLong, bearing, 
			state, sampleRate,
			finalDestination, speedInKnots);

	} 
}

// Since the algorithms may not be exact due to rounding errors, it is possible
// that we will pass the intended point.  If the aircraft is at about the right
// position, move to the next state
bool TrackGenerator::PassedPoint(LatLong origLatLong, 
	LatLong newLatLong, LatLong destination,
	FlightState state)
{

	if ((fabs(newLatLong.latitude - destination.latitude) < .0005)
		&& (fabs(newLatLong.longitude - destination.longitude) < .0005))
	{
		return true;
	}
	return false;

}

