#ifndef TRACK_APP_H
#define TRACK_APP_H

#include "NetworkInterface.h"
#include "wx/setup.h"
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "wx/grid.h"
#include "shapefil.h"
#include <map>

class TrackViewListener;
class TablePanelListener;
class FlightInfoNetworkReceiver;
class AppFrame;
class FlightInfoListener;

// ------------------------------------------------------------------------- //
// Starting point for a wxWidgets application.
//
// This creates the frames that are needed for the GUI, (including specifying
// the map that is displayed in the track display), creates the network
// interface, initializes the listeners that update the display with new 
// data that has arrived from the network.
//
class TrackApp: public wxApp
{

	virtual bool OnInit();
    virtual int OnExit();

public:

	// Returns the network interface
	NetworkInterface *GetNetworkInterface() 
	{
		return _netInterface;
	}

	// Returns the main frame of the application
	AppFrame *GetFrame()
	{
		return _frame;
	}

	// Query whether the application is shutting down.  The presenter thread
	// can use this to detect that the application is closing, to shut down
	// nicely.
	bool ShuttingDown() 
	{ 
		return _shuttingDown; 
	}

	// Returns the FlightInfoNetworkReceiver - the "presenter" in a model-view
	// -presenter pattern.
	FlightInfoNetworkReceiver *GetPresenter()
	{
		return _networkFlightInfoReceiver;
	}

	// Called back from the windows of the application, because they are
	// deleted before the application is notified that it is shutting down.
	bool RemoveDataSource(wxPanel *panel);

private:

	// This is the interface that receives track data over the all available
	// transports (such as shared memory or UDP)
	NetworkInterface *_netInterface;

	// This is the main frame of the application.
	AppFrame *_frame;

	// This queries the network and presents updates to the UI frames using
	// the two listeners, which update the data belonging to the panels, and
	// force them to refresh their UI.  These classes can be considered the
	// "presenter" classes in a model-view-presenter model. 
	FlightInfoNetworkReceiver *_networkFlightInfoReceiver;
	TrackViewListener *_trackViewListener;
	TablePanelListener *_tablePanelListener;

	// This maps from panels to listeners, and is used to detach the listeners
	// from the panels because the panels are deleted by the wxWidgets 
	// framework befor the application is notified of shutdown.
	std::map<wxPanel *, FlightInfoListener *> _dataSources;

	// Used to tell the presentation layer that the application is shutting 
	// down, so the thread should be cleaned up.
	bool _shuttingDown;

};

#endif