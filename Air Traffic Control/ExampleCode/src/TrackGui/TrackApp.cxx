
#include <string>
#include "TrackApp.h"
#include "TrackPresenter.h"
#include "TrackGUI.h"

using namespace std;


bool MyApp::OnInit() {

	_shuttingDown = false;
//		"Z:\\code\\Polaris\\Use Case 0 - Radar Tracks\\ExampleCode\\resource\\ne_110m_land\\ne_110m_land"
//		"Z:\\code\\polaris\\ne_110m_land\\ne_110m_land"
//		"Z:\\code\\polaris\\st06_d00_shp\\st06_d00"

	// TODO:  Use relative path or get it from the command line
	_frame = new AppFrame(
		this, "ATC Flight Viewer", 
		wxPoint(0, 0), wxSize(340, 650),
		"Z:\\code\\polaris\\Use Case 0 - Radar Tracks-temp\\ExampleCode\\resource\\bayarea_county2000\\bayarea_county2000");

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
	xmlFiles.push_back("file://../src/Config/flight_plan_profiles_multicast.xml");
	_netInterface = new NetworkInterface(xmlFiles);

	_networkFlightInfoReceiver = new FlightInfoNetworkReceiver(this);
	_trackViewListener = new TrackViewListener(_frame->GetTrackPanel());
	_networkFlightInfoReceiver->AddListener(_trackViewListener);
	_tablePanelListener = new TablePanelListener(_frame->GetTablePanel());
	_networkFlightInfoReceiver->AddListener(_tablePanelListener);

	_dataSources[(wxPanel *)_frame->GetTrackPanel()] =  _trackViewListener;
	_dataSources[(wxPanel *)_frame->GetTablePanel()] =  _tablePanelListener;

	_networkFlightInfoReceiver->StartReceiving();

	return true;	
}

bool MyApp::RemoveDataSource(wxPanel *panel)
{
	FlightInfoListener *listener = _dataSources[panel];
	_networkFlightInfoReceiver->RemoveListener(listener);
	return true;
}

int MyApp::OnExit() 
{
//	delete _frame;

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

IMPLEMENT_APP(MyApp)
