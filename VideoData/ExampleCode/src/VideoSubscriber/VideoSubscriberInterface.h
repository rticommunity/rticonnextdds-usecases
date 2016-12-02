/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided �as is�, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#ifndef VIDEO_SUBSCRIBER_INTERFACE_H
#define VIDEO_SUBSCRIBER_INTERFACE_H

#include "connext_cpp_common.h"
#include "CommonInfrastructure/DDSCommunicator.h"
#include "CommonInfrastructure/DDSTypeWrapper.h"
#include "CommonInfrastructure/VideoBuffer.h"

#include <map>


class VideoStreamReader;
class VideoSubscriberInterface;

// ------------------------------------------------------------------------- //
// Defines
// ------------------------------------------------------------------------- //
#define NANOSEC_TO_SEC 1000000000

// ------------------------------------------------------------------------- //
// The Video Subscriber interface is composed of a single reader of video data
// that receives the video and plays it at a certain rate.  It  
//
// Reading video  data:
// --------------------
// This class receives the video data reliably, but this can be changed in the
// video_stream_multicast.xml file. For more information on the QoS, please 
// see that file.
//
// For information on the video stream data type, please see the 
// VideoData.idl file.  
//
// For information on the quality of service for video stream data, please
// see the video_stream_multicast.xml file.
//
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// 
// VideoEventHandler:
// 
// An interface for a class that is called back by the listener that will 
// process video frames that are received in the DataReader
//
// ------------------------------------------------------------------------- //
class VideoEventHandler
{
public:
	virtual void OnFrameUpdate(EMDSBuffer *buffer, long streamId) = 0;
	virtual void OnVideoEnd() = 0;

};

// ------------------------------------------------------------------------- //
//
// VideoSubscriberInterface:
// A class that sets up the DDS interface (the network interface) of this 
// video application, including creating appropriate DDS DataWriters, DDS
// DataReaders, and all other DDS objects.
//
// This example creates a single DataReader, but the same DomainParticipant
// can be used to create DataWriters as well.
//
// ------------------------------------------------------------------------- //
class VideoSubscriberInterface  
{

public:

	// --- Constructor --- 
	VideoSubscriberInterface( 
		std::vector<std::string>qosFileNames,
		std::string videoProperties,
		bool multicastVideoStreams = false);

	// --- Destructor --- 
	~VideoSubscriberInterface();


	// This returns the VideoData receiver - a small wrapper around the 
	// StreamDataReader that initializes the reader and uses the 
	// DDS "Listener" object to be notified of video data arriving
	VideoStreamReader *GetVideoStreamReader() 
	{
		return _VideoStreamReader;
	}


	// --- Getter for Communicator --- 
	// Accessor for the communicator (the class that sets up the basic
	// DDS infrastructure like the DomainParticipant).
	// This allows access to the DDS DomainParticipant/Publisher/Subscriber
	// classes
	DDSCommunicator *GetCommunicator() 
	{
		return _communicator; 
	}

private:
	// --- Private members ---

	// This contains the calls that allow the interface to create a 
	// "DomainParticipant", the first object that must be created to 
	// communicate over a DDS middleware.
	DDSCommunicator *_communicator;


	// Used for receiving video data
	VideoStreamReader *_VideoStreamReader;


};

// ------------------------------------------------------------------------- //
//
// VideoStreamListener:
// Used for receiving video streams.  This encapsulates the concepts of a DDS
// DataReaderListener.  This receives updates of video data within a middleware
// thread.  Note that this means the thread SHOULD NOT BE BLOCKED.
//
// This listener class does nothing but call back all of the video handlers
// that are registered.  This means that the writers of video handlers need
// to ensure that they are not blocking or performing any long processing.
class VideoStreamListener : public DDS::DataReaderListener
{
public:

	// --- Constructor --- 
	VideoStreamListener(VideoStreamReader *reader) :
		_reader(reader), _last_seq_nr(0)
	{
	}


	// --- Callback for data ---
	// Notified FROM THE MIDDLEWARE THREAD that data is available.
	// notifies VideoStreamReader of data, which calls its handlers
	// HANDLERS REGISTERED WITH THE VideoStreamReader SHOULD NOT BLOCK
	virtual void on_data_available(DDS::DataReader *reader);

private:
	VideoStreamReader *_reader;
   unsigned int _last_seq_nr;
};

// ------------------------------------------------------------------------- //
//
// VideoStreamReader:
// Used for receiving video streams.  This encapsulates the concepts of a DDS
// type-specific DataReader (for type VideoStream), along with the mechanisms
// for accessing data - in this case, this allows the application to block one
// of its threads to wait for data from the VideoStreamReader.
//
// ------------------------------------------------------------------------- //
class VideoStreamReader 
{

public:

	// --- Constructor --- 
	// This creates a DDS DataReader that subscribes to video frame information
	// This uses the app object to access the DomainParticipant, and it uses 
	// the QoS profiles specified when creating the DataReader.  The XML QoS 
	// files were previously configured when the VideoSubscriberInterface's 
	// DDSCommunicator was created.
	VideoStreamReader(
		VideoSubscriberInterface *comm, 
		DDS::Subscriber *sub, 
		const std::string &qosLibrary, 
		const std::string &qosProfile,
		const std::string &videoMetadata);


	// --- Destructor --- 
	~VideoStreamReader();

	// --- Register video handler --- 
	void RegisterVideoHandler(VideoEventHandler *handler);
	void UnregisterVideoHandler(VideoEventHandler *handler);
	void NotifyHandlers(com::rti::media::generated::VideoStream *frame,
				long streamId, double timestamp);


private:
	// --- Private methods --- 

	// --- Private members ---
	std::vector<VideoEventHandler *> _eventHandlers;

	// Contains all the components needed to create the DataReader
	VideoSubscriberInterface *_communicator;

	// Application-specific DDS DataReader for receiving video stream data
	com::rti::media::generated::VideoStreamDataReader *_reader;

	// Objects to block a thread until video data arrives
	VideoStreamListener *_listener;
	
	//EMDSBuffer *_buffer;
};




#endif
