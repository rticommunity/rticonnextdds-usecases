/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided �as is�, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#ifndef VIDEO_PUBLISHER_INTERFACE_H
#define VIDEO_PUBLISHER_INTERFACE_H

#include <sstream>
#include "connext_cpp_common.h"
#include "CommonInfrastructure/DDSCommunicator.h"
#include "CommonInfrastructure/DDSTypeWrapper.h"

class VideoPublisherDiscoveryListener;
class CodecCompatibleHandler;

// ------------------------------------------------------------------------- //
//
// The video publisher interface provides streaming video data over the network 
// (or shared memory) to other applications that are interested in video data.
//
// Writing streaming video data:
// -----------------------------
// This application sends video data, configured to behave as streaming data
//
// For information on the video stream data type, please see the 
// VideoData.idl file.  
//
// For information on the quality of service for video stream data, please
// see the video_stream_multicast.xml file.
//
// ------------------------------------------------------------------------- //
class VideoPublisherInterface
{

public:

	// --- Constructor --- 
	// Initializes the video publisher interface, including creating a 
	// DomainParticipant, creating all publishers and subscribers, topics 
	// writers and readers.  Takes as input a vector of xml QoS files that
	// should be loaded to find QoS profiles and libraries.
	VideoPublisherInterface(std::vector<std::string> xmlFiles,
			CodecCompatibleHandler *codecCompatibilityHandler = NULL);

	// --- Destructor --- 
	~VideoPublisherInterface();

	// --- Getter for Communicator --- 
	// Accessor for the communicator (the class that sets up the basic
	// DDS infrastructure like the DomainParticipant).
	// This allows access to the DDS DomainParticipant/Publisher/Subscriber
	// classes
	DDSCommunicator *GetCommunicator() 
	{ 
		return _communicator; 
	}

	// --- Sends the video data ---
	// Uses DDS interface to send a video stream efficiently over the 
	// network or shared memory to interested applications subscribing to
	// streaming video.
	bool Write(DdsAutoType<com::rti::media::generated::VideoStream> data);

	// --- Deletes the video stream ---
	// "Deletes" the video stream from the system - removing the DDS 
	// instance from all applications.
	bool Delete(DdsAutoType<com::rti::media::generated::VideoStream> data);

private:
	// --- Private members ---

	// Used to create basic DDS entities that all applications need
	DDSCommunicator *_communicator;

	// Video stream publisher specific to this application
	com::rti::media::generated::VideoStreamDataWriter *_writer;
};


class CodecCompatibleHandler
{
public:
	virtual bool CodecsCompatible(std::string codecString) = 0;
};

// ------------------------------------------------------------------------- //
//
// The video publisher discovery listener is used to listen to discovery of
// remote video subscriber applications.  
//
// Listening for video metadata:
// -----------------------------
//
// This is a listener that is installed on the local DomainParticipant.  It is
// notified when the DomainParticipant discovers a remote DataReader.  At that
// time, it checks whether the DataReader:
//        1) Has a topic that this application interested in (VIDEO_TOPIC)
//        2) Has sent metadata as a part of the discovery data using the 
//           user_data QoS.  This metadata should include information about the
//           codecs that the reader can decode.  If the DataReader does not 
//           support a codec that this application is writing, we will print an
//           error, and we will not send video data to the DataReader.
//
// ------------------------------------------------------------------------- //
class VideoPublisherDiscoveryListener : public DDS::DataReaderListener
{
public:

	// --- Constructor --- 
	VideoPublisherDiscoveryListener(CodecCompatibleHandler *handler)
		: _handler(handler)
	{
	}

	// --- Listener callback for discovery of remote DataReader --- 
	// Inherited from the DDSDataReaderListener class
	virtual void on_data_available(DDS::DataReader *reader);

private:
	CodecCompatibleHandler *_handler;
};

#endif
