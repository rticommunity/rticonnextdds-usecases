/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
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
//
// Starting point for a wxWidgets application.
//
// This creates the frames that are needed for the GUI, (including specifying
// the map that is displayed in the track display), creates the network
// interface, initializes the listeners that update the display with new 
// data that has arrived from the network.
//
// ------------------------------------------------------------------------- //
class TrackApp: public wxApp
{

	// --- Handle initialization and shutdown events --- //
	virtual bool OnInit();
    virtual int OnExit();

public:

	// --- Getter for the network interface --- //
	// Accessor for the network interface class that has the flight plan
	// and track reader classes.
	NetworkInterface *GetNetworkInterface() 
	{
		return _netInterface;
	}

	// --- Getter for the main frame --- //
	// Returns the main frame of the application
	AppFrame *GetFrame()
	{
		return _frame;
	}

	// --- Query for shutdown --- //
	// Query whether the application is shutting down.  The presenter thread
	// can use this to detect that the application is closing, to shut down
	// nicely.
	bool ShuttingDown() 
	{ 
		return _shuttingDown; 
	}

	// --- Set shutdown --- //
	// Set the application's shutting down state .  
	void SetShuttingDown(bool shutDown) 
	{ 
		_shuttingDown = shutDown; 
	}

	// --- Getter for the presenter --- //
	// Returns the FlightInfoNetworkReceiver - the "presenter" in a model-view
	// -presenter pattern.
	FlightInfoNetworkReceiver *GetPresenter()
	{
		return _networkFlightInfoReceiver;
	}

	// --- Removes a data source from the application --- //
	// Called back from the application's windows to remove the data source,
	// because they are deleted before the application is notified that it is 
	// shutting down.  Without this, the data source will have bad pointers
	// to the windows, and can crash.
	bool RemoveDataSource(wxPanel *panel);

private:
	// --- Private members ---

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