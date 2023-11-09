/*
 * (c) 2021 Copyright, Real-Time Innovations, Inc. (RTI) All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the software solely for use with RTI Connext DDS.  Licensee may
 * redistribute copies of the software provided that all such copies are
 * subject to this license. The software is provided "as is", with no warranty
 * of any type, including any warranty for fitness for any purpose. RTI is
 * under no obligation to maintain or support the software.  RTI shall not be
 * liable for any incidental or consequential damages arising out of the use or
 * inability to use the software.
 */

#include "TrackPresenter.h"
#include "TrackApp.h"
#include "TrackGUI.h"

#include <vector>
#include <sstream>

using namespace std;

// ------------------------------------------------------------------------- //
// Class FlightInfoNetworkReceiver
//
// A class that is the Presenter part of a model-view-presenter architecture.
// This is responsible for checking for changes to the model.  It contains a
// thread that checks for the current state of the flight data, and notifies
// the UI that the data has changed.
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// Create a new network receiver class.  This class is the glue between
// the UI and the data source - in this case, the DDS network data
// that is arriving asynchronously.
FlightInfoNetworkReceiver::FlightInfoNetworkReceiver(TrackApp* parent)
        : _shuttingDown(false), _app(parent)
{
  
}

// ------------------------------------------------------------------------- //
// Destructor
FlightInfoNetworkReceiver::~FlightInfoNetworkReceiver()
{

}

// ------------------------------------------------------------------------- //
// Observer pattern for notifications. The track presenter will notify various
// UI listeners that a track has been deleted, and the UI listeners can redraw
// the UI as necessary.  This allows a single update to notify multiple windows
// or panels that a track has been deleted.
void FlightInfoNetworkReceiver::NotifyListenersDeleteTrack(
        const std::vector<FlightInfo*> flights)
{
    for (std::vector<FlightInfoListener*>::iterator it = _listeners.begin();
         it != _listeners.end();
         ++it) {
        // Notify the UI listeners that the track has been deleted
        if (false == (*it)->TrackDelete(flights)) {
            std::stringstream errss;
            errss << "NotifyListenersDeleteTrack(): error deleting track.";
            throw errss.str();
        }
    }
}

// ------------------------------------------------------------------------- //
// Observer pattern for notifications. The track presenter will notify various
// UI listeners that a track has been updated, and the UI listeners can redraw
// the UI as necessary.  This allows a single update to notify multiple windows
// or panels that a track has been updated.
void FlightInfoNetworkReceiver::NotifyListenersUpdateTrack(
        const std::vector<FlightInfo*> flights)
{
    for (std::vector<FlightInfoListener*>::iterator it = _listeners.begin();
         it != _listeners.end();
         ++it) {
        // Notify the UI listeners that tracks have been updated
        if (false == (*it)->TrackUpdate(flights)) {
            std::stringstream errss;
            errss << "NotifyListenersUpdateTrack(): error updating track.";
            throw errss.str();
        }
    }
}

// ------------------------------------------------------------------------- //
// Remove listeners.  This must be called before shutdown, because the frames
// that are updating may be deleted before the data source.  So, the listeners
// must be removed from the UI before it shuts down.
void FlightInfoNetworkReceiver::RemoveListener(
        const FlightInfoListener* listener)
{
    std::vector<FlightInfoListener*>::iterator toErase;

    for (std::vector<FlightInfoListener*>::iterator it = _listeners.begin();
         it != _listeners.end();
         ++it) {
        if ((*it) == listener) {
            toErase = it;
        }
    }

    _listeners.erase(toErase);
}


// ------------------------------------------------------------------------- //
// This starts receiving the network data - or, more accurately, this starts
// the process of accessing data that is already being received asynchronously
// over the network as soon as the DDS discovery process is complete.
void FlightInfoNetworkReceiver::StartReceiving()
{
#if defined RTI_WIN32
    HANDLE hThread;
    DWORD id;

    hThread = CreateThread(NULL, 0,
              (LPTHREAD_START_ROUTINE)FlightInfoNetworkReceiver::ReceiveTracks,
              _app, 0, &id);
#elif defined RTI_LINUX
    pthread_t tid;
    pthread_create(&tid, NULL, FlightInfoNetworkReceiver::ReceiveTracks, _app);
#else
    #error Uknow Architecture
#endif
}

// ------------------------------------------------------------------------- //
// 1. Retrieves the latest flight plan information from the model
// 2. Converts the TrackData / FlightPlan data from the network form of the
// data to the form that is used by the  UI.
void FlightInfoNetworkReceiver::PrepareUpdate(
        TrackApp* app,
        vector<com::atc::generated::Track> updateData,
        vector<FlightInfo*>* flightData)
{
    FlightPlanReader* planReader =
            app->GetNetworkInterface()->GetFlightPlanReader();

    for (unsigned int i = 0; i < updateData.size(); i++) {
        // Allocate a flight info object.  This will be filled in with
        // the flight plan information.
        FlightInfo* flightInfo = new FlightInfo;
        flightInfo->_track = updateData[i];


        // This copies a flight plan from the middleware into
        // the object passed in
        planReader->GetFlightPlan(
                updateData[i].flightId().c_str(),
                &flightInfo->_plan);
        flightData->push_back(flightInfo);
    }
}

// ------------------------------------------------------------------------- //
// Update UI when track data changes.
void* FlightInfoNetworkReceiver::ReceiveTracks(void* param)
{
    TrackApp* app = (TrackApp*) param;

    // Get access to the data reader objects that are receiving data over the
    // network asynchronously.
    NetworkInterface* netInterface = app->GetNetworkInterface();

    TrackReader* reader = netInterface->GetTrackReader();
    FlightPlanReader* planReader = netInterface->GetFlightPlanReader();
    vector<com::atc::generated::Track> tracks;
    vector<com::atc::generated::Track> tracksDeleted;
    vector<FlightInfo*> flights;
    vector<FlightInfo*> flightsDeleted;

    // This periodically wakes up and updates the UI with the latest track
    // information that is available from the middleware, which has been
    // collecting it asynchronously.
    dds::core::Duration uiUpdatePeriod(0, 200000000);

    while (!app->ShuttingDown()) {
        // Note that this API allocates tracks that are a copy of tracks
        // in the queue.  This allows us to pass in an empty vector and
        // use the data in it however we want.
        reader->GetCurrentTracks(tracks, tracksDeleted);

        if (app->ShuttingDown()) {
            return NULL;
        }

        if (!tracks.empty()) {
            // Convert the data type from the network type to the type expected
            // by the UI listeners.
            PrepareUpdate(app, tracks, &flights);

            // Notify the listeners that there is an upate to the track list
            app->GetPresenter()->NotifyListenersUpdateTrack(flights);
        }
        if (!tracksDeleted.empty()) {
            // Convert the data type from the network type to the type expected
            // by the UI listeners.
            PrepareUpdate(app, tracksDeleted, &flightsDeleted);

            // Notify the listeners that there is an deletion from the track
            // list
            app->GetPresenter()->NotifyListenersDeleteTrack(flightsDeleted);
        }

        tracks.clear();
        tracksDeleted.clear();

        // Delete the "FlightInfo" structures we have just generated.  There
        // are more efficient ways to do this by preallocating, but this is okay
        // for this simple use case
        for (unsigned int i = 0; i < flights.size(); i++) {
            delete flights[i];
        }

        flights.clear();

        // Delete the "FlightInfo" structures we have just generated.  There
        // are more efficient ways to do this by preallocating, but this is okay
        // for this simple use case
        for (unsigned int i = 0; i < flightsDeleted.size(); i++) {
            delete flightsDeleted[i];
        }

        flightsDeleted.clear();

        // Sleep until the next UI refresh
        rti::util::sleep(uiUpdatePeriod);
    }
    return NULL;
}
