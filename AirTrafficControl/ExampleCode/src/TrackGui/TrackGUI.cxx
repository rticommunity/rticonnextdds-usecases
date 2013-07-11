/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#include "TrackGUI.h"
#include "TrackPresenter.h"
#include "TrackApp.h"

using namespace std;

class TrackApp;

enum
{
    ID_Quit = 1,
    ID_About,
};


#define SFO_LAT 37.6190
#define SFO_LONG -122.3749

#define EARTH_MEAN_RADIUS_KM 6371


AppFrame::AppFrame(TrackApp *app, 
	const wxString& title, 
	const wxPoint& pos, 
	const wxSize& size, 
	const string filePath)
	: wxFrame(NULL, -1, title, pos, size),
	_app(app)
{
	wxMenu *menuFile = new wxMenu;

	menuFile->Append( ID_About, _("&About...") );
	menuFile->AppendSeparator();
	menuFile->Append( ID_Quit, _("E&xit") );

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append( menuFile, _("&File") );

	SetMenuBar( menuBar );
	CreateStatusBar();
	SetStatusText( _("Track Viewer") );


	// Note: 
	// May want to parse shape file earlier and set the panel size based on the relative 
	// size of the geography, or change the radar circle to an ellipse to match the 
	// view.
	wxSplitterWindow *splitter = new 
		wxSplitterWindow(this, -1, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
	splitter->SetSashGravity(0.5);

	// Open up the panel that shows tracks, and the panel that shows a grid of
	// flight data.
	_panel = new TrackPanel( splitter, 1, _("Track Viewer"), 
		wxPoint(0, 0), wxSize(450, 480), filePath);

	_tablePanel = new TablePanel(splitter, 2, _("Flight Info"), 
		wxPoint(0, _panel->GetSize().GetY()),
		wxSize(450, 100));

	// Make the panels resize when the window resizes
	wxSizer *sizerMain = new wxBoxSizer(wxVERTICAL);
	sizerMain->Add(splitter, 1, wxEXPAND, 0);

	wxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
	sizerTop->Add(_panel, 1, wxEXPAND);

	wxSizer *sizerBottom = new wxBoxSizer(wxVERTICAL);
	sizerBottom->Add(_tablePanel,  1, wxEXPAND);

	splitter->SplitHorizontally(_panel, _tablePanel);
	SetSizer(sizerMain);
	sizerMain->SetSizeHints(this);


}

void AppFrame::OnQuit(wxCommandEvent& event) 
{
	GetApp()->RemoveDataSource(_tablePanel);

	delete _panel;
}

TrackPanel::TrackPanel(wxWindow *parent, wxWindowID id, const wxString& title, 
	const wxPoint& pos, const wxSize& size, std::string filePath)
	: wxPanel(parent, -1, pos, size)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	_latlongProjection = NULL;
	_mercatorProjection = NULL;

	_mutex = new OSMutex();

	SHPHandle handle = SHPOpen(filePath.c_str(), "r+b");
	int numEntities = 0;
	int shapeType = 0;
	double minBound[4], maxBound[4];
	SHPGetInfo(handle, &numEntities, &shapeType, minBound, maxBound);
	for (int i = 0; i < numEntities; i++) 
	{
		SHPObject *shapeObject = 
			SHPReadObject(handle, i);
		_shapeObjects.push_back(shapeObject);
	}

	CalculateGeoMinMax();
	CalculateCoordinateForWindowSize();

}


// Clears the current list of points, since they are likely to all change
// before the next repainting.
void TrackPanel::ClearPointsLists()
{
	for (unsigned int i = 0; i < _pointsLists.size(); i++) 
	{
		wxPointList *list = _pointsLists[i];

		for (unsigned int j = 0; j < list->size(); j++) 
		{
			delete (*list)[j];
		}

		delete list;
	}
	_pointsLists.clear();
}

void TrackPanel::Calculate80KmNorthFromSFO(wxRealPoint *latLong)
{
	double finalKm = 80;
//	double degreesInRads = degrees * M_PI / 180;
	double degreesInRads = 0;

	double latInRads = SFO_LAT * M_PI / 180;
	double longInRads = SFO_LONG * M_PI / 180;
	double distInRads = finalKm / EARTH_MEAN_RADIUS_KM;
	double bearing = degreesInRads;

	double temp1 = sin(latInRads) * cos(distInRads);
	double temp2 = cos(latInRads) * sin(distInRads) * cos(bearing);
	double newLatInRads = 
		asin (  temp1 + 
			  temp2 );
	double newLongInRads =
		longInRads + atan2(sin(bearing)*sin(distInRads)*cos(latInRads),
					cos(distInRads) - (sin(latInRads) * sin(newLatInRads)));

	// Normalize to -180 - 180
	newLongInRads = fmod((newLongInRads + 3 * M_PI), (2 * M_PI)) - M_PI; 

	latLong->y = newLatInRads / M_PI * 180;
	latLong->x = newLongInRads / M_PI * 180;


}
// Draw a circle centered on SFO to indicate the distance that the radar can
// display
void TrackPanel::DrawRadarCircleSFO(wxBufferedPaintDC &dc)
{


	double y1,x1;

	// Convert the coordinates to UTM from Lat/Long
	ConvertLatLongToUTM(&y1, &x1, SFO_LAT, SFO_LONG);

	wxRealPoint coord;
	// 
	ConvertMapCoordToWindow(&coord, wxRealPoint(x1,y1), 			
		_maxX,_maxY,_minX,_minY, 
		GetClientRect().width, GetClientRect().height);

	// Radar range: estimating ~80 km - a reasonable range
	// for surveillance radar
	wxRealPoint northLatLong;
	Calculate80KmNorthFromSFO(&northLatLong);

	double y2,x2;
	ConvertLatLongToUTM(&y2, &x2, northLatLong.y, northLatLong.x);

	wxRealPoint coord2;


	ConvertMapCoordToWindow(&coord2, wxRealPoint(x2,y2), 			
		_maxX,_maxY,_minX,_minY, 
		GetClientRect().width, GetClientRect().height);

	double circleHeight = coord.y - coord2.y;
	
	wxBrush oldBrush = dc.GetBrush();
	wxPen oldPen = dc.GetPen();
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.SetPen(*wxCYAN_PEN);
	dc.DrawCircle(coord,circleHeight);

	dc.SetBrush(oldBrush);
	dc.SetPen(oldPen);
}

// Repaint the polygons and the points indicating aircraft on the map.  This 
// might be more efficient if we invalidate only the parts of the rectangle
// that actuall change.
void TrackPanel::OnPaint(wxPaintEvent& paintEvt)
{
	wxBufferedPaintDC dc(this);

	wxBrush brush;
	brush.SetColour(0, 50, 150);
	dc.SetBackground(brush);

	dc.Clear();

		
	for (unsigned int i = 0; i < _pointsLists.size(); i++) 
	{

		dc.DrawPolygon(_pointsLists[i]);

	}

	DrawRadarCircleSFO(dc);

	for (
		std::map<long, wxPoint>::iterator it = 
		_trackPoints.begin(); it != _trackPoints.end(); ++it) 
	{
		wxPen pen(*wxRED);
		wxPen prevPen = dc.GetPen();
		dc.SetPen(pen);
		dc.DrawCircle((*it).second, 3);
		dc.SetPen(prevPen);
	}



}

// Calculate the minimum and maximum points in the geometry that is being
// displayed. 
void TrackPanel::CalculateGeoMinMax()
{
	vector<wxRealPoint *> realPoints;

	if (_shapeObjects.size() == 0) 
	{
		return;
	}
	double xMax = _shapeObjects[0]->padfX[0];
	double yMax = _shapeObjects[0]->padfY[0];
	double xMin = _shapeObjects[0]->padfX[0];
	double yMin = _shapeObjects[0]->padfY[0];

	for (unsigned int i = 0; i < _shapeObjects.size(); i++) 
	{
		for (int j = 0; j < _shapeObjects[i]->nVertices; j++) 
		{
			if (_shapeObjects[i]->padfX[j] > xMax) 
			{
				xMax = _shapeObjects[i]->padfX[j];
			}
			if (_shapeObjects[i]->padfY[j] > yMax) 
			{
				yMax = _shapeObjects[i]->padfY[j];
			}
			if (_shapeObjects[i]->padfX[j] < xMin) 
			{
				xMin = _shapeObjects[i]->padfX[j];
			}
			if (_shapeObjects[i]->padfY[j] < yMin) 
			{
				yMin = _shapeObjects[i]->padfY[j];
			}

		}
	}

	_maxX = xMax;
	_maxY = yMax;
	_minX = xMin;
	_minY = yMin;

}

// Map from the coordinates in UTM or Lat/Long into a set of points that are
// used when drawing in the actual window.  
// This is only called initially, or when resizing the window.
void TrackPanel::CalculateCoordinateForWindowSize()
{

	for (unsigned int i = 0; i < _shapeObjects.size(); i++) 
	{

		for (int j = 0; j < _shapeObjects[i]->nParts; j++) 
		{

			wxPointList *points = new wxPointList;
			int nVerticesPerPart = 0;
			if (j == _shapeObjects[i]->nParts - 1) 
			{
				int startOfPart = _shapeObjects[i]->panPartStart[j];
				nVerticesPerPart = _shapeObjects[i]->nVertices -
					_shapeObjects[i]->panPartStart[j];
			} else 
			{
				nVerticesPerPart = _shapeObjects[i]->panPartStart[j + 1] - 
					_shapeObjects[i]->panPartStart[j];
			}
			for (int k = _shapeObjects[i]->panPartStart[j]; k < 
						_shapeObjects[i]->panPartStart[j] + nVerticesPerPart;
						k++) 
			{
				wxRealPoint coord;
				ConvertMapCoordToWindow(&coord, 
					wxRealPoint( _shapeObjects[i]->padfX[k], 
					_shapeObjects[i]->padfY[k]),
					_maxX,_maxY,_minX,_minY, 
					GetClientRect().width, GetClientRect().height
					);
				
				points->Append(new wxPoint(coord));
			}

			_pointsLists.push_back(points);
		}	
	}
}

// Use the proj library to convert between latitude/longitude and mercator 
// projections.  This allows us to receive flight information in lat/long and 
// to draw it on a map that is in mercator (UTM) coordinates.
void TrackPanel::ConvertLatLongToUTM(double *northing, double *easting, 
	double latitude, double longitude)
{
	*northing = latitude * DEG_TO_RAD;
	*easting = longitude * DEG_TO_RAD;
	if (_mercatorProjection == NULL)
	{
		_mercatorProjection = pj_init_plus("+proj=utm +zone=10 +ellps=WGS84");
		if (_mercatorProjection == NULL)
		{
			int error = pj_ctx_get_errno(pj_get_default_ctx());
			std::stringstream errss;
			errss << 
				"ConvertLatLongToUTM(): unable to create the map projection."
				<<" Error: " << error;
			throw errss.str();
		}
	}
	if (_latlongProjection == NULL)
	{
		 _latlongProjection = pj_init_plus("+proj=latlong +ellps=clrk66");
		if (_latlongProjection == NULL)
		{
			int error = pj_ctx_get_errno(pj_get_default_ctx());
			std::stringstream errss;
			errss << 
				"ConvertLatLongToUTM(): unable to create the map projection."
				<<" Error: " << error;
			throw errss.str();
		}
	}
	pj_transform(_latlongProjection, _mercatorProjection, 1, 1, easting, 
		northing, NULL);
}


// This does the actual conversion from map coordinates to window coordinates,
// which: 
//     a) assume that 0,0 is in the upper-left-hand corner of the window.
//     b) may be distorted based on the size of the window
void TrackPanel::ConvertMapCoordToWindow(wxRealPoint *coord, 
							wxRealPoint latLong, double maxX, double maxY,
							double minX, double minY, int windowSizeX, 
							int windowSizeY)
{
	double xZeroBased = latLong.x - minX;
	double yShift = 0 - maxY;
	double yZeroBasedReversed = latLong.y + yShift;
	double xDistance = maxX - minX;

	double xSize = maxX - minX;
	double yDistance = maxY - minY;
		
	coord->x = ((xZeroBased)  * windowSizeX) / xDistance;

	double yAspectRatio = yDistance / xDistance * windowSizeX;
	coord->y = -yZeroBasedReversed * yAspectRatio / yDistance;

}

// When the window is resized, we remove all points, we calculate the points
// for the new window size, and we refresh the window
void TrackPanel::OnSize(wxSizeEvent &event)
{
	ClearPointsLists();
	CalculateCoordinateForWindowSize();
	Refresh();

}

// Delete the track panel, and clear the list of points that it has been
// storing that indicate the geometry of the map.  Free the mercator
// projection data, and free the map data itself.
TrackPanel::~TrackPanel() 
{
	_mutex->Lock();
	AppFrame *appFrame = (AppFrame *)GetParent()->GetParent();
	appFrame->GetApp()->RemoveDataSource((wxPanel *)this);

	for (unsigned int i = 0; i < _pointsLists.size(); i++) 
	{	
		wxPointList *list = _pointsLists[i];
		for (unsigned int j = 0; j < _pointsLists[i]->size(); j++) 
		{
			delete (*list)[j];
		}

		list->Clear();
		delete list;
	}
	_pointsLists.clear();

	for (unsigned int i = 0; i < _shapeObjects.size(); i++) 
	{
		SHPDestroyObject(_shapeObjects[i]);
	}
	_shapeObjects.clear();

	_trackPoints.clear();

	pj_free(_latlongProjection);
	pj_free(_mercatorProjection);

	_mutex->Unlock();
	delete _mutex;
	Close(true);
}

// A panel that is used to 
TablePanel::TablePanel(wxWindow *parent, wxWindowID id, const wxString& title, 
		const wxPoint& pos, 
		const wxSize& size)
	: wxPanel(parent, -1, pos, size)
{
	
	_grid = new wxGrid( this,
                    -1,
                    wxPoint( 0, 0 ),
                    wxSize( 400, 300 ) );

	// Then we call CreateGrid to set the dimensions of the grid
	// (64 rows and 8 columns in this example)
	_grid->CreateGrid( 64, 10 );
	// We can set the sizes of individual rows and columns
	// in pixels
	_grid->SetRowSize( 0, 60 );
	_grid->SetColSize( 0, 80 );

	// Set the column headers
	_grid->SetColLabelValue(0, "Radar ID" );
	_grid->SetColLabelValue(1, "Track ID" );
	_grid->SetColLabelValue( 2, "Flight ID" );

	_grid->SetColLabelValue(3, "Latitude");
	// Specify that latitude and longitude columns are numeric.
	_grid->SetColFormatFloat(3, 6, 4);

	_grid->SetColFormatFloat(4, 6, 4);
	// Specify that latitude and longitude columns are numeric.
	_grid->SetColLabelValue(4, "Longitude");

	_grid->SetColLabelValue(5, "Departed From");
	_grid->SetColLabelValue(6, "Destination");
	_grid->SetColLabelValue(7, "Estimated Arrival");

}

// Delete the table panel, and remove the data source so it can be
// cleaned up nicely.  If you do not detach the data source before this
// panel is deleted, it can lead to bad pointers.  
TablePanel::~TablePanel()
{
	AppFrame *appFrame = (AppFrame *)GetParent()->GetParent();
	appFrame->GetApp()->RemoveDataSource((wxPanel *)this);

	delete _grid;
}

// Resize the grid when it receives an on size event.
void TablePanel::OnSize(wxSizeEvent &event)
{

	_grid->SetSize(event.GetSize().GetX(),
		event.GetSize().GetY());

}

// Update a row of the table when the data values of the flight information
// has changed.
void TablePanel::UpdateRow(const FlightInfo &flight)
{
	_grid->BeginBatch();
	bool exists = false;
	for (int i = 0; i < _grid->GetNumberRows(); i++ )
	{

		long radarIdCell = -1;
		if (!_grid->GetCellValue(i,0).IsEmpty()) 
		{
			_grid->GetCellValue(i,0).ToLong(&radarIdCell);
		}
		long trackIdCell = -1;
		if (!_grid->GetCellValue(i,1).IsEmpty()) 
		{
			_grid->GetCellValue(i,1).ToLong(&trackIdCell);
		}

		if (radarIdCell == flight._track.radarId && trackIdCell == 
			flight._track.trackId) 
		{
			exists = true;

			// Only update the cell value if this has changed
			if (0 != strcmp(_grid->GetCellValue(i,2).c_str(), 
				flight._track.flightId))
			{
				_grid->SetCellValue(i, 2, wxString(flight._track.flightId));
			}

			_grid->SetCellValue(i, 3, wxString::Format(wxT("%f"), flight._track.latitude));
			_grid->SetCellValue(i, 4, wxString::Format(wxT("%f"), flight._track.longitude));
			if (_grid->GetCellValue(i, 5) != flight._plan.departureAerodrome)
			{
				_grid->SetCellValue(i, 5, wxString(flight._plan.departureAerodrome));
			}
			if (_grid->GetCellValue(i, 5) != flight._plan.destinationAerodrome)
			{
				_grid->SetCellValue(i, 6, wxString(flight._plan.destinationAerodrome));
			}
			char date[6];
			sprintf(date, "%02i:%02i", flight._plan.estimatedHours,
				flight._plan.estimatedMinutes);
			if (_grid->GetCellValue(i, 7) != date)
			{
				_grid->SetCellValue(i, 7, wxString(date) );
			}
			break;
		}
	}

	if (!exists)
	{
		for (int i = 0; i < _grid->GetNumberRows(); i++ )
		{
			if (_grid->GetCellValue(i,0).IsEmpty() &&
				_grid->GetCellValue(i,1).IsEmpty()) 
			{

				_grid->SetCellValue(i,0, wxString::Format(wxT("%i"), 
					flight._track.radarId));
				_grid->SetCellValue(i,1, wxString::Format(wxT("%i"), 
					flight._track.trackId));
				_grid->SetCellValue(i,2, wxString( 
					flight._track.flightId));
				_grid->SetCellValue(i,3, wxString::Format(wxT("%f"), 
					flight._track.latitude));
				_grid->SetCellValue(i,4, wxString::Format(wxT("%f"), 
					flight._track.longitude));
				_grid->SetCellValue(i, 5, wxString(flight._plan.departureAerodrome));
				_grid->SetCellValue(i, 6, wxString(flight._plan.destinationAerodrome));
				char date[6];
				sprintf(date, "%02i:%02i", flight._plan.estimatedHours,
					flight._plan.estimatedMinutes);
				_grid->SetCellValue(i, 7, wxString(date) );
				break;
			}
		}
	}
	_grid->EndBatch();
}

// WxWidgets event table declarations.

BEGIN_EVENT_TABLE(TablePanel,wxPanel)
	EVT_SIZE(TablePanel::OnSize)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(TrackPanel,wxPanel)
    EVT_PAINT(TrackPanel::OnPaint)
	EVT_SIZE(TrackPanel::OnSize)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(AppFrame, wxFrame)
    EVT_MENU(ID_Quit,  AppFrame::OnQuit)
END_EVENT_TABLE()



