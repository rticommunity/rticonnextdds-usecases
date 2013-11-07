/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#include <iostream>
#include "TrackGenerator.h"
#include "RadarInterface.h"

// ------------------------------------------------------------------------- //
//
// This contains the glue code that ties the radar generator
// to the DDS network middleware layer.
//
// This inherits from a listener class provided by the Radar.
//
// It takes in a RadarWriter object and uses that to write data.  (The 
// RadarWriter object is created as part of the RadarInterface).  This is not
// responsible for deleting the RadarWriter object.  
//
// You must ensure that the thread that calls this class is shut down before 
// the RadarInterface (and the RadarWriter) are deleted.
//
// ------------------------------------------------------------------------- //

// A listener that is receiving updates about new generated tracks
// and sending them out over DDS
class DDSRadarListener : public TrackListener 
{
public:

	// --- Constructor ---
	// Initializes the RadarWriter object, and sets the 
	// Radar Id that becomes part of the data.
	DDSRadarListener(RadarWriter *writer, long radarId) 
		: _writer(writer), _radarId(radarId)
	{
		com::rti::atc::generated::TrackTypeSupport::initialize_data(&_track);

	}

	// --- Destructor ---
	~DDSRadarListener() 
	{
	}


	// --- Update track over network ---
	// Converts from the radar's data type to the data type that will be sent
	// over the middleware, and then sends the radar data.  It is not 
	// strictly necessary in this example that we maintain multiple data types
	// for track data, but it is fairly common that your sensor will provide one
	// set of data types, and you will be using a slightly (or sometimes very)
	// different data type over the network
	virtual bool TrackUpdate(const GeneratorTrack &track) 
	{

		// Convert from generator format to network format
		RadarAdapter::AdaptToTrack(_track, track);
		_track.radarId = _radarId;

		try 
		{
			// Send the data over the network
			_writer->PublishTrack(_track);
		} catch (std::string str) 
		{
			std::cout << "Failure to write track data: " << str.c_str() << 
				std::endl;
			return false;
		}

		return true;
	}

	// --- Delete track over network ---
	// Sends an update saying that a track has been dropped.  This uses the 
	// same RadarWriter to notify other applications that the track has
	// been dropped that is used to send track updates.
	virtual bool TrackDelete(const GeneratorTrack &track) 
	{

		// Convert from generator format to network format
		RadarAdapter::AdaptToTrack(_track, track);
		_track.radarId = _radarId;

		try 
		{
			// Send the track deletion over the network
			_writer->DeleteTrack(_track);
		} catch (std::string str) 
		{
			std::cout << "Failure to delete track data: " << str.c_str() << 
				std::endl;
			return false;
		}
		return true;
	}

private:
	// --- Private members ---

	// Writes track data over network
	RadarWriter *_writer;

	// Network data type of a track
	DdsAutoType<com::rti::atc::generated::Track> _track;

	// The ID of this radar
	long _radarId;
};