/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/
#include <stdio.h>
#include <vector>
#include <iostream>

#include "../CommonInfrastructure/VideoSource.h"
#include "../Generated/VideoData.h"
#include "../Generated/VideoDataSupport.h"
#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "VideoPublisherInterface.h"

#ifdef WIN32
#include <stdlib.h>
#include "Shlwapi.h"
#endif

using namespace std;

void PrintHelp();

// ------------------------------------------------------------------------- //
//
// FrameHandler:
//
// A class that receives a notification from the GStreamer framework that 
// a frame is available to be processed.  This copies that frame into a 
// DDS VideoStream data type, and calls Write() to send it over the network. 
//
// ------------------------------------------------------------------------- //
class FrameHandler : public EMDSFrameHandler
{

public:
	// --- Constructor ---
	FrameHandler() : _seqNum(0)
	{
		srand(time(NULL));
		_streamId = rand();
		std::cout << "Created frame publisher with unique stream ID: " << 
			_streamId << std::endl;

	}

	// ------------------------------------------------------------------------
	// Frame Ready:
	// When the video framework calls back this listener to tell it that a
	// frame is ready to be processed, this callback copies it into an RTI
	// Connext DDS data object and publishes it over DDS.
	virtual void FrameReady(void *obj, EMDSBuffer *buffer) 
	{
		// Has a copy of the DDS interface that is used to publish data over 
		// the network (or shared memory).
		VideoPublisherInterface *pubInterface = 
			(VideoPublisherInterface *)obj;

		// Creates a VideoStream data object
		VideoStream *streamData = 
				VideoStreamTypeSupport::create_data();
		if (buffer->GetSize() > 0)
		{
			// Sets the frame information within the data to the correct size
			// based on the buffer size
			streamData->frame.ensure_length(
				buffer->GetSize(), buffer->GetSize());

			// Copy the data from the buffer into the object to be sent using
			// the middleware.
			streamData->frame.from_array( 
				(DDS_Octet *)buffer->GetData(), buffer->GetSize());

			// Set the sequence number
			streamData->sequence_number = _seqNum;
			_seqNum++;
		}

		streamData->flags = buffer->GetFlags();
		streamData->stream_id = _streamId;
	
		// Sending the data over the network (or shared memory)
		pubInterface->Write(*streamData);

		// Cleaning up the data sample
		VideoStreamTypeSupport::delete_data(streamData);
	}

	virtual void EOSHandler(void *obj, EMDSBuffer *buffer) 
	{
	}

private:

	// --- Private members --- 
	int _seqNum;

	// Each video streamer has a different stream ID
	int _streamId;

};


// ------------------------------------------------------------------------- //
//
// CodecCompatibilityCheck:
//
// A class that acts as part of the interface between the video processing 
// and the middleware.  This is called back from the VideoPublisherInterface
// when that object discovers a DataReader that is interested in the same
// Topic, stored in the constant VIDEO_TOPIC.  
// 
// This queries the video framework to see if the codecs are compatible with
// each other.
// ------------------------------------------------------------------------- //
class CodecCompatibilityCheck : public CodecCompatibleHandler
{
public:

	// --- Constructor --- 
	CodecCompatibilityCheck(EMDSVideoSource *videoSource)
		: _source(videoSource), _discoveredCompatibleReader(false)
	{
	}

	// Calls the gstreamer framework to see if the subscribing app's codec
	// is compatible with what we are sending.  If not, we return false.
	virtual bool CodecsCompatible(std::string codecString)
	{
		cout << "CODEC " << codecString << endl;
		if (_source->IsMetadataCompatible(codecString)) 
		{
			_discoveredCompatibleReader = true;
		}
		return _discoveredCompatibleReader;
	}

	bool DiscoveredCompatibleReader()
	{
		return _discoveredCompatibleReader;
	}

private:

	// --- Private members --- 
	EMDSVideoSource *_source;
	bool _discoveredCompatibleReader;

};

// ----------------------------------------------------------------------------
//
// main function.  Prepares the video pipeline and the video publisher
// interface (the class that sends video data over RTI Connext DDS)
//
int main (int argc, char *argv[])
{

	cout << "--- Starting publisher application. --- " << endl;
	cout << "This application will read a video file, and publish it over RTI"
		<< " Connext DDS " << endl << "middleware" << endl;
	bool multicastAvailable = true;

	for (int i = 0; i < argc; i++)
	{
		if (0 == strcmp(argv[i], "--no-multicast"))
		{
			multicastAvailable = false;
		} else if (0 == strcmp(argv[i], "--help"))
		{
			PrintHelp();
			return 0;
		} else if (i > 0)
		{
			// If we have a parameter that is not the first one, and is not 
			// recognized, return an error.
			cout << "Bad parameter: " << argv[i] << endl;
			PrintHelp();
			return -1;
		}

	}

	// Set up paths for XML files.  The profiles are for applications that 
	// have no multicast available at all, or that have multicast available
	// on the network.
	vector<string> xmlFiles;

	if (multicastAvailable)
	{
		// Adding the XML files that contain profiles used by this application
		xmlFiles.push_back(
			"file://../../../src/Config/base_profile_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/video_stream_multicast.xml");
	}
	else
	{
		// Adding the XML files that contain profiles used by this application
		xmlFiles.push_back(
			"file://../../../src/Config/base_profile_no_multicast.xml");
		xmlFiles.push_back(
			"file://../../../src/Config/video_stream_no_multicast.xml");

	}

#ifdef WIN32
	char fullPath[512];
	std::string relativePath = "..\\..\\..\\resource\\bigbuck.webm";

    if (NULL == _fullpath(fullPath, relativePath.c_str(), 512))
	{
		cout << "Error getting file path" << endl;
	}
	EMDSVideoSource *videoSource = new EMDSVideoSource(
		fullPath);
#else
	std::string relativePath = "../../../resource/bigbuck.webm";
	char fullPath[PATH_MAX];
	if (NULL == realpath(relativePath.c_str(), fullPath))
	{
		cout << "Error getting the file path" << endl;
	}
	EMDSVideoSource *videoSource = new EMDSVideoSource(
		fullPath );
#endif

	// If the video source was not created correctly, return an error.
	if (videoSource == NULL)
	{
		cout << "Failed to create video source" << endl;
		return -1;
	}

	// Initialize the video source, including opening the file
	if (videoSource->Initialize() != 0)
	{
		cout << "Failed to initialize video" << endl;
		return -1;
	}

	// Listener class to receive notifications of remote Video Subscriber apps
	// This checks if the remote application has a codec that is compatible
	// with what this application sends.
	CodecCompatibilityCheck compatibilityCheck(videoSource);

	// The Video Publisher Interface is responsible for:
	// 1. Publishing video data over RTI Connext DDS 
	// 2. Receiving discovery notifications about video subscribers that have 
	//    been found.  If those have the correct Topic, and also contain
	//    user_data QoS with codec information, we check whether they have
	//    a codec that is compatible with what we are sending.  We only send if
	//    the subscriber app has a compatible codec to us.  Note that this can
	//    be used for a variety of uses, such as determining video quality, etc

	try 
	{
		VideoPublisherInterface videoInterface(xmlFiles, 
			&compatibilityCheck);

		// Callback from the gstreamer framework that is providing us with video
		// frames.  This frameHandler uses the VideoPublisherInterface's Write() 
		// method to write frames over the network.
		FrameHandler *frameHandler = new FrameHandler();
		videoSource->SetNewFrameCallbackHandler(
				frameHandler,
				(void *)&videoInterface);

		// Wait for compatible DataReaders to come online
		while (!compatibilityCheck.DiscoveredCompatibleReader())
		{
			DDS_Duration_t send_period = {2,0};
			cout << "Waiting for a compatible video subscriber to come "
				<< "online" << endl;
			NDDSUtility::sleep(send_period);
		}

		// If we have found a compatible Video Subscriber, we start publishing.
		videoSource->Start();

		// Loop forever here
		while (1) 
		{
			DDS_Duration_t send_period = {0,100000000};
			NDDSUtility::sleep(send_period);
		}

	} 
	catch (string message)
	{
		cout << "Application exception" << message << endl;
	}


}

void PrintHelp()
{
	cout << "Valid options are: " << endl;
	cout << 
		"    --no-multicast" <<
		"       Do not use any multicast, including for discovery"
		<< endl << 
		"                         " <<
		"(note you must edit XML config to include IP" << endl <<
		"                         " <<
		"addresses)" 
		<< endl;

}

