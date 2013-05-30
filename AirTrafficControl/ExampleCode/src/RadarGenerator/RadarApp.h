#include "TrackGenerator.h"
#include "RadarInterface.h"


// ------------------------------------------------------------------------- //
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
// ------------------------------------------------------------------------- //

// A listener that is receiving updates about new generated tracks
// and sending them out over DDS
class DDSRadarListener : public TrackListener {
public:

	// Constructor: Initializes the RadarWriter object, and sets the 
	// Radar Id that becomes part of the data.
	DDSRadarListener(RadarWriter *writer, long radarId) 
		: _writer(writer), _radarId(radarId)
	{
		com::rti::atc::generated::TrackTypeSupport::initialize_data(&_track);

	}

	// Destructor
	~DDSRadarListener() 
	{
	}


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
			printf("Failure to write track data: %s", str.c_str());
			return false;
		}

		return true;
	}

	// Sends an update saying that a track has been dropped.  This uses the 
	// same RadarWriter to notify other applications that the track has
	// been dropped that is used to send track updates.
	virtual bool TrackDelete(const GeneratorTrack &track) {

		// Convert from generator format to network format
		RadarAdapter::AdaptToTrack(_track, track);
		_track.radarId = _radarId;

		try {
			// Send the track deletion over the network
			_writer->DeleteTrack(_track);
		} catch (std::string str) {
			printf("Failure to delete track data: %s", str.c_str());
			return false;
		}
		return true;
	}

private:
	RadarWriter *_writer;
	DdsAutoType<com::rti::atc::generated::Track> _track;
	long _radarId;
};