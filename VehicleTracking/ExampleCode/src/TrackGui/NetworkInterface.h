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

#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include <vector>
#include <dds/dds.hpp>
#include "../Generated/AirTrafficControl.hpp"

class FlightPlanReader;
class TrackReader;


// ------------------------------------------------------------------------- //
//
// NetworkInterface:
// A class that sets up the DDS interface (the network interface) of this
// GUI application, including creating appropriate DDS DataWriters, DDS
// DataReaders, and all other DDS objects.
//
// In this example, the GUI is only subscribing to data, so this class creates
// two DDS DataReaders and no DDS DataWriters.
//
// ------------------------------------------------------------------------- //
class NetworkInterface {
public:
    // --- Constructor ---
    // The constructor creates all the necessary DDS objects (in this case,
    // a DomainParticipant, a Subscriber, and objects wrapping two DDS
    // DataReaders.)  This also configures the XML QoS configuration files that
    // should be used by the application.
    NetworkInterface(std::vector<std::string> qosFileNames);

    // --- Destructor ---
    ~NetworkInterface();

    // --- Getter for the flight plan reader ---
    // Accessor for the object that receives flight plans from the network
    FlightPlanReader* GetFlightPlanReader()
    {
        return _flightPlanReader;
    }

    // --- Getter for the track reader ---
    // Accessor for the object that receives track updates from the network
    TrackReader* GetTrackReader()
    {
        return _trackReader;
    }

private:
    // --- Private members ---

    // Flight plan receiver specific to this application
    FlightPlanReader* _flightPlanReader;

    // Track receiver specific to this application
    TrackReader* _trackReader;
};


// ------------------------------------------------------------------------- //
//
// FlightPlanReader:
// A wrapper for a DDS DataReader, that receives flight plan data, leaves it
// in the middleware queue, and queries the flight plan when a track updates.
//
// ------------------------------------------------------------------------- //
class FlightPlanReader {
public:
    // --- Constructor ---
    // Subscribes to flight plan information
    FlightPlanReader(
            NetworkInterface* app,
            const std::string& qosLibrary,
            const std::string& qosProfile);

    // --- Destructor ---
    ~FlightPlanReader();

    // --- Wake up the reader thread if it is waiting on data ---
    void NotifyWakeup();

    // --- Retrieve flight plan ---
    // This example is not being notified when new flight plans arrive, and
    // instead queries the middleware for a particular flight plan update
    // when it is interested in it.  It queries the middleware queue by
    // flight ID.
    void GetFlightPlan(
            const char* flightId,
            com::atc::generated::FlightPlan* plan);

private:
    // --- Private members ---

    // Contains all the components needed to create the DataReader
    NetworkInterface* _app;

    // The DDS DataReader of flight plans
    dds::sub::DataReader<com::atc::generated::FlightPlan> _fpReader =
            dds::core::null;
    ;

    // The mechanisms that cause a thread to wait until flight plan data
    // becomes available, and to be woken up when the data arrives
    dds::core::cond::WaitSet _waitSet;
    dds::core::cond::GuardCondition _shutDownNotifyCondition;
};

// ------------------------------------------------------------------------- //
//
// TrackReader:
// A wrapper for a DDS DataReader, that blocks an application thread, waiting
// to receive notifications of track data.
//
// ------------------------------------------------------------------------- //
class TrackReader {
public:
    // --- Constructor ---
    // Subscribes to flight plan information
    TrackReader(
            NetworkInterface* app,
            const std::string& qosLibrary,
            const std::string& qosProfile);

    // --- Destructor ---
    ~TrackReader();

    // --- Waiting for tracks ---
    // This waits for new tracks to become available, and notifies the
    // application that there are new tracks or deleted tracks.
    void WaitForTracks(
            std::vector<com::atc::generated::Track>& tracksUpdated,
            std::vector<com::atc::generated::Track>& tracksDeleted);

    // --- Retreiving current track updates ---
    // This retrieves track updates from the middleware queue.  This is used
    // to poll for all the current track updates from the middleware.  This
    // keeps a second vector that includes all tracks that have been deleted.
    void GetCurrentTracks(
            std::vector<com::atc::generated::Track>& tracksUpdated,
            std::vector<com::atc::generated::Track>& tracksDeleted);

    // --- Wake up the reader thread if it is waiting on data ---
    void NotifyWakeup();

private:
    // --- Private members ---

    // Contains all the components needed to create the DataReader
    NetworkInterface* _app;

    // The DDS DataReader of tracks
    dds::sub::DataReader<com::atc::generated::Track> _reader = dds::core::null;

    // The mechanisms that cause a thread to wait until flight plan data
    // becomes available, and to be woken up when the data arrives
    dds::core::cond::WaitSet _waitset;
    dds::core::cond::GuardCondition _shutDownNotifyCondition;
    dds::core::cond::StatusCondition* status_cond;
};

#endif
