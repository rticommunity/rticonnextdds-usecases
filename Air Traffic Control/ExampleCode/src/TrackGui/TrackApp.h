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

class MyApp: public wxApp
{

	virtual bool OnInit();
    virtual int OnExit();

public:
	NetworkInterface *GetNetworkInterface() 
	{
		return _netInterface;
	}
	AppFrame *GetFrame()
	{
		return _frame;
	}

	bool ShuttingDown() 
	{ 
		return _shuttingDown; 
	}

	FlightInfoNetworkReceiver *GetPresenter()
	{
		return _networkFlightInfoReceiver;
	}

	bool RemoveDataSource(wxPanel *panel);

private:

	NetworkInterface *_netInterface;
	AppFrame *_frame;
	FlightInfoNetworkReceiver *_networkFlightInfoReceiver;
	TrackViewListener *_trackViewListener;
	TablePanelListener *_tablePanelListener;
	std::map<wxPanel *, FlightInfoListener *> _dataSources;

	bool _shuttingDown;

};

#endif