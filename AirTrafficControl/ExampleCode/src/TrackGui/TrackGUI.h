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
#include "shapefil.h"
#include "proj_api.h"

class FlightInfoNetworkReceiver;





// ------------------------------------------------------------------------- //
//
// TrackPanel:
// A class that draws a map, and tracks on a wxWidgets panel
//
// ------------------------------------------------------------------------- //
class TrackPanel : public wxPanel 
{

public:
	TrackPanel(wxWindow *parent, wxWindowID id, const wxString& title, 
		const wxPoint& pos, const wxSize& size, std::string filePath);
	~TrackPanel();

	void ClearPoints()
	{
		_mutex->Lock();

		_trackPoints.clear();

		_mutex->Unlock();
	}

	void UpdatePoint(long trackId, wxRealPoint point)
	{
		_mutex->Lock();
		wxRealPoint coord(0,0);
		wxRealPoint latLong(point.x, point.y);

		ConvertMapCoordToWindow(&coord, latLong, _maxX, _maxY, _minX, _minY, 
			GetClientRect().width, GetClientRect().height);

		_trackPoints[trackId] = coord;
		_mutex->Unlock();
	}

	void AddOrUpdatePoint(long trackId, wxRealPoint point)
	{

		wxRealPoint coord(0,0);

		if (_trackPoints.find(trackId) != _trackPoints.end())
		{
			UpdatePoint(trackId, point);
			return;
		}
			
		_mutex->Lock();
		wxRealPoint latLong(point.x, point.y);

		ConvertMapCoordToWindow(&coord, latLong, _maxX, _maxY, _minX, _minY, 
			GetClientRect().width, GetClientRect().height);
		
		_trackPoints[trackId] = coord;

		_mutex->Unlock();
	}

	void OnPaint(wxPaintEvent& paintEvt);
	void DrawRadarCircleSFO(wxBufferedPaintDC &dc);

	void CalculateCoordinateForWindowSize();
	void ClearPointsLists();

	void OnSize(wxSizeEvent &event);	




	void CalculateGeoMinMax();
	
	void ConvertLatLongToUTM(double *northing, double *easting, 
						double latitude, double longitude);

	void ConvertMapCoordToWindow(wxRealPoint *coord, 
		wxRealPoint latLong, double maxX,
		double maxY, double minX, double minY,
		int windowSizeX, int windowSizeY);

	void Calculate80KmNorthFromSFO(wxRealPoint *latLong);


	OSMutex *_mutex;
	std::vector<SHPObject *> _shapeObjects;
	std::map<long, wxPoint> _trackPoints;
	std::vector<wxPointList *> _pointsLists;
//	wxPointList _trackPoints;
	double _minX, _minY, _maxX, _maxY;
	projPJ _latlongProjection;
	projPJ _mercatorProjection;
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
	TablePanel(wxWindow *parent, wxWindowID id, const wxString& title, 
		const wxPoint& pos, 
		const wxSize& size);
	~TablePanel();
	void OnSize(wxSizeEvent &event);
	void PrepareUpdate() 
	{
		_grid->BeginBatch();
	}
	void UpdateComplete()
	{
		_grid->EndBatch();
	}
	void UpdateRow(const FlightInfo &track);
	void AddPoint(wxRealPoint point);
	void OnQuit(wxCommandEvent &event);

private:
	wxGrid *_grid;
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

	AppFrame(TrackApp *app, 
		const wxString& title, 
		const wxPoint& pos, 
		const wxSize& size,
		std::string filePath);	

	TrackPanel *GetTrackPanel()
	{
		return _panel; 
	}
	TablePanel *GetTablePanel()
	{
		return _tablePanel; 
	}
	TrackApp *GetApp()
	{ 
		return _app;
	}
	void OnSize(wxSizeEvent &event);
	void OnQuit(wxCommandEvent &event);

private:
	TrackPanel *_panel;
	TablePanel *_tablePanel;
	TrackApp *_app;

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
	TrackViewListener(TrackPanel *panel)
	{
		_panel = panel;
	}
	virtual bool TrackUpdate(const std::vector<FlightInfo *> flights) 
	{

//		_panel->ClearPoints();
		for (unsigned int i = 0; i < flights.size(); i++)
		{
			double x,y;


			_panel->ConvertLatLongToUTM(&y,&x,
				flights[i]->_track->latitude, 
				flights[i]->_track->longitude);
			_panel->AddOrUpdatePoint(flights[i]->_track->trackId, 
				wxRealPoint(x,y));
		}
		_panel->Refresh();
		return true;
	}

	virtual bool TrackDelete(const std::vector<FlightInfo *> flights) 
	{
		return true;
	}


private:
	TrackPanel *_panel;
};

class TablePanelListener : public FlightInfoListener
{
public:
	TablePanelListener(TablePanel *panel)
	{
		_panel = panel;
	}
	virtual bool TrackUpdate(const std::vector<FlightInfo *> flights) 
	{
		_panel->PrepareUpdate();
		for (unsigned int i = 0; i < flights.size(); i++)
		{
			_panel->UpdateRow(*flights[i]);
		}
		_panel->UpdateComplete();
		return true;

	}
	virtual bool TrackDelete(const std::vector<FlightInfo *> flights) 
	{
		return true;
	}


private:
	TablePanel *_panel;
};

#endif
