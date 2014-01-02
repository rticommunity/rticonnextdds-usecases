/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

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
bool TrackApp::OnInit() 
{

	_shuttingDown = false;
	bool multicastAvailable = true;

	for (int i = 0; i < argc; i++)
	{
		if (0 == strcmp(argv[i], "--no-multicast"))
		{
			multicastAvailable = false;
		}
	}

	// --- Setting the map file path --- //
	string filePath;
#ifdef RTI_WIN32
	filePath = "..\\..\\..\\resource\\bayarea_county2000\\bayarea_county2000";
#else
	filePath = "../../../resource/bayarea_county2000/bayarea_county2000";
#endif
	_frame = new AppFrame(
		this, "ATC Flight Viewer", 
		wxPoint(0, 0), wxSize(450, 700),
		filePath);

	wxPoint point(300, 300);
	_frame->SetPosition(point);
	_frame->Show(true);
	SetTopWindow(_frame);

	// Tune the radar for low latency.  The two QoS profiles are 
	// defined in USER_QOS_PROFILES.xml
	vector<string> xmlFiles;

	if (multicastAvailable)
	{
		// Adding the XML files that contain profiles used by this application
		xmlFiles.push_back(
			"file://../../../src/Config/base_profile_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/radar_profiles_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/flight_plan_profiles_multicast.xml");
	}
	else 
	{
		// Adding the XML files that contain profiles used by this application
		xmlFiles.push_back(
			"file://../../../src/Config/base_profile_no_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/radar_profiles_no_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/flight_plan_profiles_no_multicast.xml");
	}

	// If the DDS network interface fails to run (due to mising XML files or
	// a missing license) catch the exception here instead of letting the GUI
	// framework handle it.
	try 
	{
		_netInterface = new NetworkInterface(xmlFiles);
	}
	catch (string message)
	{
		cout << message << endl;
		return false;
	}

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

	// This can be null if an error occurs while initializing
	if (listener != NULL)
	{
		_networkFlightInfoReceiver->RemoveListener(listener);
	}

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
