
#include <string>
#include "TrackApp.h"
#include "TrackPresenter.h"
#include "TrackGUI.h"

using namespace std;

// ------------------------------------------------------------------------- //
// Starting point for a wxWidgets application.
//
// This creates the frames that are needed for the GUI, (including specifying
// the map that is displayed in the track display), creates the network
// interface, initializes the listeners that update the display with new 
// data that has arrived from the network.
//
bool TrackApp::OnInit() {

	_shuttingDown = false;

	_frame = new AppFrame(
		this, "ATC Flight Viewer", 
		wxPoint(0, 0), wxSize(340, 650),
		"..\\resource\\bayarea_county2000\\bayarea_county2000");

	wxPoint point(300, 300);
	_frame->SetPosition(point);
	_frame->Show(true);
	SetTopWindow(_frame);

	// Tune the radar for low latency.  The two QoS profiles are 
	// defined in USER_QOS_PROFILES.xml
	vector<string> xmlFiles;

	// Adding the XML files that contain profiles used by this application
	xmlFiles.push_back("file://../src/Config/multicast_base_profile.xml");
	xmlFiles.push_back("file://../src/Config/radar_profiles_multicast.xml");
	xmlFiles.push_back(
		"file://../src/Config/flight_plan_profiles_multicast.xml");
	_netInterface = new NetworkInterface(xmlFiles);

	// This class accesses the data that arrives over the network.  This 
	// creates a thread, and uses it so periodically poll the network interface
	// for the current track data that it has received.
	_networkFlightInfoReceiver = new FlightInfoNetworkReceiver(this);
	_trackViewListener = new TrackViewListener(_frame->GetTrackPanel());
	_networkFlightInfoReceiver->AddListener(_trackViewListener);
	_tablePanelListener = new TablePanelListener(_frame->GetTablePanel());
	_networkFlightInfoReceiver->AddListener(_tablePanelListener);

	// This associates the listeners with the panels that they are updating.
	// This is necessary because the listeners must be removed before the 
	// frames are deleted - or else the application may crash at shutdown.
	_dataSources[(wxPanel *)_frame->GetTrackPanel()] =  _trackViewListener;
	_dataSources[(wxPanel *)_frame->GetTablePanel()] =  _tablePanelListener;

	// This starts the thread that accesses the data from the network.
	_networkFlightInfoReceiver->StartReceiving();

	return true;	
}

// ------------------------------------------------------------------------- //
// This disassociates a listener from a panel, allowing the panel to be deleted
// separately from the listener.
bool TrackApp::RemoveDataSource(wxPanel *panel)
{
	FlightInfoListener *listener = _dataSources[panel];
	_networkFlightInfoReceiver->RemoveListener(listener);
	return true;
}

// ------------------------------------------------------------------------- //
// This cleans up memory as the application is shutting down.
int TrackApp::OnExit() 
{

	delete _trackViewListener;
	_trackViewListener = NULL;
	delete _tablePanelListener;
	_tablePanelListener = NULL;
	_shuttingDown = true;
	delete _netInterface;
	_netInterface = NULL;
	delete _networkFlightInfoReceiver;
	_networkFlightInfoReceiver = NULL;

	return 0;
}

// ------------------------------------------------------------------------- //
// wxWidgets macro for an application class
IMPLEMENT_APP(TrackApp)
