
#ifndef TRACK_GUI_H
#define TRACK_GUI_H

#include <string.h>
#include <vector>
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
		for (unsigned int i = 0; i < _trackPoints.size(); i++) 
		{
			delete _trackPoints[i];
		}
		_trackPoints.Clear();
	}

	void AddPoint(wxRealPoint point)
	{

		wxRealPoint coord(0,0);
			
		wxRealPoint latLong(point.x, point.y);

		ConvertMapCoordToWindow(&coord, latLong, _maxX, _maxY, _minX, _minY, 
			GetClientRect().width, GetClientRect().height);
			_trackPoints.Append(new wxPoint(coord));

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




	std::vector<SHPObject *> _shapeObjects;
	std::vector<wxPointList *> _pointsLists;
	wxPointList _trackPoints;
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

	AppFrame(MyApp *app, 
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
	MyApp *GetApp()
	{ 
		return _app;
	}
	void OnSize(wxSizeEvent &event);
	void OnQuit(wxCommandEvent &event);

private:
	TrackPanel *_panel;
	TablePanel *_tablePanel;
	MyApp *_app;

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

		_panel->ClearPoints();
		for (unsigned int i = 0; i < flights.size(); i++)
		{
			double x,y;


			_panel->ConvertLatLongToUTM(&y,&x,
				flights[i]->_track->latitude, 
				flights[i]->_track->longitude);
			_panel->AddPoint(wxRealPoint(x,y));
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
		for (unsigned int i = 0; i < flights.size(); i++)
		{
			_panel->UpdateRow(*flights[i]);
		}
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