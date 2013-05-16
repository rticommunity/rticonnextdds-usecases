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
	FlightInfoNetworkReceiver(TrackApp *parent); 
	~FlightInfoNetworkReceiver();

	static void ReceiveTracks(void *param);

	void NotifyListenersUpdateTrack(const std::vector<FlightInfo *> flights);
	void NotifyListenersDeleteTrack(const std::vector<FlightInfo *> flights);
	bool IsShuttingDown() const { return _shuttingDown; }
	void AddListener(FlightInfoListener *listener) {
		_listeners.push_back(listener);
	}

	void RemoveListener(const FlightInfoListener *listener);

	void StartReceiving();

private:
	bool _shuttingDown;
	TrackApp* _app;
	std::vector<FlightInfoListener *> _listeners;

	// Control access to listeners that may be
	// accessed by multiple threads
	OSMutex *_mutex;
};

#endif