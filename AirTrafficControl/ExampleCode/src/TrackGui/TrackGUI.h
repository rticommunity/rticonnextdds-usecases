/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#ifndef TRACK_GUI_H
#define TRACK_GUI_H

#include <string.h>
#include <vector>
#include <map>
// Must be inclued before wxWidgets headers
#include "../CommonInfrastructure/OSAPI.h"
#include "NetworkInterface.h"
#include "TrackPresenter.h"
#include "FlightInfo.h"
#include "wx/setup.h"
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "wx/grid.h"
#include "wx/splitter.h"
#include "shapefil.h"
#include "proj_api.h"

class FlightInfoNetworkReceiver;


// ------------------------------------------------------------------------- //
//
// TrackPanel:
// A class that draws a map, and aircraft positions on a wxWidgets panel
//
// ------------------------------------------------------------------------- //
class TrackPanel : public wxPanel 
{

public:

	// --- Constructor and Destructor --- 
	TrackPanel(wxWindow *parent, wxWindowID id, const wxString& title, 
		const wxPoint& pos, const wxSize& size, std::string filePath);

	~TrackPanel();


	// --- Update the position of a point (aircraft) --- 
	void UpdatePoint(long trackId, wxRealPoint point);

	// --- Add/Update the position of a point (aircraft) --- 
	//
	// If the point already exists, update its position.  If it does not, add
	// a new point to the list.
	void AddOrUpdatePoint(long trackId, wxRealPoint point);

	// --- Delete a point (aircraft) --- 
	void DeletePoint(long trackId);

	// --- Paint events for drawing aircraft movement --- 
	void OnPaint(wxPaintEvent& paintEvt);
	void OnSize(wxSizeEvent &event);	

	// --- Draw a circle around a radius of SFO --- 
	void DrawRadarCircleSFO(wxBufferedPaintDC &dc);

	// --- Translate from lat/long to window position --- 
	void CalculateCoordinateForWindowSize();

	// --- Clear the lists of points of the map ---
	void ClearPointsLists();

	// --- Decide the max and minimum lat/long or UTM in the view ---
	void CalculateGeoMinMax();

	// --- Convert between lat/long values and UTM values ---
	// The map is in UTM, so must do a conversion between lat/long and UTM
	void ConvertLatLongToUTM(double *northing, double *easting, 
						double latitude, double longitude);

	// --- Convert between lat/long or UTM values and window points ---
	void ConvertMapCoordToWindow(wxRealPoint *coord, 
		wxRealPoint latLong, double maxX,
		double maxY, double minX, double minY,
		int windowSizeX, int windowSizeY);

	// --- Calculate point representing 80 KM from SFO ---
	// Have chosen the radius around SFO as 80KM.  This is hard-coded
	// for the example.
	void Calculate80KmNorthFromSFO(wxRealPoint *latLong);

	// --- Private members ---

	// Mutex for handling multi-threaded access to the GUI drawing
	OSMutex *_mutex;

	// The shape objects read from a shapefile that are used to draw a map
	std::vector<SHPObject *> _shapeObjects;

	// The points where each aircraft is currently located, in window 
	// coordinates
	std::map<long, wxPoint> _trackPoints;

	// The points representing the geometry of the map, in window coordinates
	std::vector<wxPointList *> _pointsLists;

	// Maximum X/Y values of the map
	double _minX, _minY, _maxX, _maxY;

	// Information about the projection used for the map 
	projPJ _latlongProjection;
	projPJ _mercatorProjection;

	// Handle to the shapes within the shapefile
	SHPHandle _handle;

	// wxWidgets macro for events
	DECLARE_EVENT_TABLE()
};

// ------------------------------------------------------------------------- //
//
// TablePanel:
// A class that fills in a table panel with information about tracks and flight
// plan data, such as expected arrival time.
//
// ------------------------------------------------------------------------- //
class TablePanel : public wxPanel
{
public:	

	// --- Constructor and Destructor --- 
	TablePanel(wxWindow *parent, wxWindowID id, const wxString& title, 
		const wxPoint& pos, 
		const wxSize& size);
	~TablePanel();

	// --- Size event --- 
	void OnSize(wxSizeEvent &event);

	// --- Quit event --- 
	void OnQuit(wxCommandEvent &event);


	// --- Grid update methods --- 
	void PrepareUpdate() 
	{
		_grid->BeginBatch();
	}

	void UpdateComplete()
	{
		_grid->EndBatch();
	}

	void UpdateRow(const FlightInfo &track);
	void DeleteRow(const FlightInfo &track);
	void AddPoint(wxRealPoint point);

private:

	// --- Private members ---
	wxGrid *_grid;

	// wxWidgets macro for events
	DECLARE_EVENT_TABLE()

};



// ------------------------------------------------------------------------- //
//
// AppFrame:
// Application window frame that contains the TrackPanel and the TablePanel.
//
// ------------------------------------------------------------------------- //
class AppFrame : public wxFrame
{
public:

	// --- Constructor and Destructor ---  --- 
	AppFrame(TrackApp *app, 
		const wxString& title, 
		const wxPoint& pos, 
		const wxSize& size,
		std::string filePath);	

	~AppFrame();

	// --- Accessor for panels --- 
	TrackPanel *GetTrackPanel()
	{
		return _panel; 
	}
	TablePanel *GetTablePanel()
	{
		return _tablePanel; 
	}

	// --- Accessor for TrackApp --- 
	TrackApp *GetApp()
	{ 
		return _app;
	}

	// --- Size event --- 
	void OnSize(wxSizeEvent &event);

	// --- Quit event --- 
	void OnQuit(wxCommandEvent &event);

private:

	// --- Private members ---
	TrackPanel *_panel;
	TablePanel *_tablePanel;
	TrackApp *_app;

	// wxWidgets macro for events
	DECLARE_EVENT_TABLE()

};




// ------------------------------------------------------------------------- //
//
// TrackViewListener:
// This listener class is installed on the TrackPresenter, and it updates the
// Track view UI whenever the presenter calls it back to announce that there 
// is a new update of track data.  This causes the track viewer to refresh its
// view and repaint.
//
// ------------------------------------------------------------------------- //

class TrackViewListener : public FlightInfoListener
{
public:

	// --- Constructor --- 
	TrackViewListener(TrackPanel *panel)
	{
		_panel = panel;
	}

	// --- Callback to update track data when it changes --- 
	// This accesses the track drawing panel and notifies the panel
	// that the points have been updated.  This also forces it to 
	// redraw. 
	virtual bool TrackUpdate(const std::vector<FlightInfo *> flights); 

	// --- Callback to delete track data when it changes --- 
	virtual bool TrackDelete(const std::vector<FlightInfo *> flights);


private:

	// --- Private members ---
	TrackPanel *_panel;
};

class TablePanelListener : public FlightInfoListener
{
public:

	// --- Constructor --- 
	TablePanelListener(TablePanel *panel)
	{
		_panel = panel;
	}

	// --- Callback to update track data when it changes --- 
	// This accesses the track grid panel and notifies the panel
	// that the track data have been updated.  This also forces it to 
	// redraw. 
	virtual bool TrackUpdate(const std::vector<FlightInfo *> flights);

	// --- Callback to delete track data when it changes --- 
	virtual bool TrackDelete(const std::vector<FlightInfo *> flights);

private:

	// --- Private members ---
	TablePanel *_panel;
};


#endif
