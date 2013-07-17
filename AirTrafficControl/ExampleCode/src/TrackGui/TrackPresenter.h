/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#ifndef TRACK_PRESENTER_H
#define TRACK_PRESENTER_H

#include <vector>
#include "FlightInfo.h"

// ------------------------------------------------------------------------- //
//
// Classes that are used to present data from the network interface to the 
// application.  This is the connection between what happens in the network
// and the UI.
//
// ------------------------------------------------------------------------- //


class TrackApp;
class OSMutex;

// ------------------------------------------------------------------------- //
//
// Listener interface for classes that will receive updates from the 
// presentation classes, and will notify the UI that it needs to update.
// ------------------------------------------------------------------------- //

class FlightInfoListener
{
public:

	virtual bool TrackUpdate(const std::vector<FlightInfo *> flights) = 0;
	virtual bool TrackDelete(const std::vector<FlightInfo *> flights) = 0;
	virtual ~FlightInfoListener() {}
};

// ------------------------------------------------------------------------- //
//
// FlightInfoNetworkReceiver:
// The model in this case is stored in the middleware, so this class is the
// presenter of a Model-View-Presenter pattern.  This receives notifications 
// of changes to the model - when track data arrives.
//
// This notifies the view of updates to the model by using TrackListeners
//
// ------------------------------------------------------------------------- //
class FlightInfoNetworkReceiver 
{
public:
	// --- Constructor and destructor --- 
	FlightInfoNetworkReceiver(TrackApp *parent); 
	~FlightInfoNetworkReceiver();

	// --- Create thread for receiving --- 
	// Creates a new thread that will call ReceiveTracks()
	void StartReceiving();

	// --- Check for receipt of track data ---
	// 
	// This loops until the application is shutting down, and checks for
	// updates to track data.  If there is new track data, it notifies
	// any listeners (observers) that the track information has been
	// updated.
	static void ReceiveTracks(void *param);

	// --- Add or remove listeners --- 
	// Adds a listener that will be notified of track updates
	void AddListener(FlightInfoListener *listener) 
	{
		_listeners.push_back(listener);
	}

	// Removes a listener that will no longer be notified of track updates
	void RemoveListener(const FlightInfoListener *listener);


	// --- Notify listeners of track state updates --- 
	void NotifyListenersUpdateTrack(const std::vector<FlightInfo *> flights);
	void NotifyListenersDeleteTrack(const std::vector<FlightInfo *> flights);

	// --- Is shutting down? --- 
	bool IsShuttingDown() const 
	{ 
		return _shuttingDown; 
	}

private:
	// --- Private methods --- 

	// Convert from network formats of data to the formats expected by the 
	// GUI that uses the data.
	static void PrepareUpdate(
		TrackApp *app,
		std::vector< DdsAutoType<com::rti::atc::generated::Track> > 
				*updateData,
		std::vector<FlightInfo *> *flightData);

	// --- Private members --- 
	bool _shuttingDown;
	TrackApp* _app;
	std::vector<FlightInfoListener *> _listeners;

	// Control access to listeners that may be
	// accessed by multiple threads
	OSMutex *_mutex;
};

#endif
