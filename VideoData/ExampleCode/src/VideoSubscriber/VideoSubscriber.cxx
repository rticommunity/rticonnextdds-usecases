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
#include <glib.h>
#include <gst/gst.h>
#include <vector>
#include <iostream>

#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "../Generated/VideoData.h"
#include "../Generated/VideoDataSupport.h"
#include "../CommonInfrastructure/VideoBuffer.h"
#include "../CommonInfrastructure/VideoOutput.h"

#include "VideoSubscriberInterface.h"

using namespace std;

void PrintHelp();


// ------------------------------------------------------------------------- //
//
// VideoDisplayHandler:
//
// A class that receives the notification update from the middleware that a
// new frame has arrived, and passes it to the GStreamer video framework.
//
// ------------------------------------------------------------------------- //
class VideoDisplayHandler : public VideoEventHandler
{
public:
	VideoDisplayHandler(EMDSVideoOutput *outputHandler, bool *finishRun)
			: _outputHandler(outputHandler), _finish(finishRun),
			_streamId(-1)
	{
	}

	virtual void OnFrameUpdate(EMDSBuffer *buffer, long streamId)
	{
		// The first time we get a stream, set the value of the 
		// stream ID
		if (_streamId == -1)
		{
			_streamId = streamId;
		}

		// This example can handle only one video stream at a time.  If we see
		// a stream ID other than the one we are processing, don't process it.
		if (_streamId != streamId)
		{
			return;
		}

		_outputHandler->GetFrameHandler()->FrameReady(_outputHandler, buffer);
	}

	virtual void OnVideoEnd()
	{
		*_finish = true;
	}

private:

	// --- Private members --- 
	EMDSVideoOutput *_outputHandler;

	long _streamId;

	bool *_finish;
};

// ------------------------------------------------------------------------- //
//
// main function.  This function:
//   1. Sets up the video display, which uses the GStreamer framework
//   2. Retrieves the metadata from that framework to determine which codec(s)
//      this application can handle.
//   3. Initializes the video subscriber interface, which uses RTI Connext DDS
//      to receive streaming video data from the network (or shared memory),
//   4. Creates a video display handler, and registers it with the video 
//      subscriber interface.  This gets called back by the RTI Connext DDS
//      middleware, and calls the display framework to actually display the
//      video.
//
// ------------------------------------------------------------------------- //
int main (int argc, char *argv[])
{
	std::cout << "--- Starting subscriber application. ---" << std::endl;
	std::cout << "This application will subscribe to a video feed over RTI"
		<< " Connext DDS " << std::endl << "middleware" << std::endl;

	bool multicastAvailable = true;
	bool multicastVideoData = false;

	for (int i = 0; i < argc; i++)
	{
		if (0 == strcmp(argv[i], "--multicast"))
		{
			if (multicastAvailable == false)
			{
				cout << "Cannot specify --multicast and --no-multicast" 
					<< endl;
				return -1;
			}
			multicastVideoData = true;
		} else if (0 == strcmp(argv[i], "--no-multicast"))
		{
			if (multicastVideoData == true)
			{
				cout << "Cannot specify --multicast and --no-multicast"
					<< endl;
				return -1;
			}
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

	try 
	{
		// Create the video framework components that will be used to display the
		// video.
		EMDSVideoOutput *vout = new EMDSVideoDisplayOutput();
		if (vout == NULL) 
		{
			std::cout << "Error, video not created" << std::endl;
		}

		// Query the metadata from the framework, such as what codecs this 
		// application can support.
		std::string videoMetadata = 
			((EMDSVideoDisplayOutput *)vout)->GetStreamMetadata();

		// Create the RTI Connext DDS video interface to the application, which 
		// receives updates of video frames from the network, and gives them to
		// the display handler.  This also takes in the video metadata, and 
		// sends it using the DDS USER_DATA QoS as a part of the discovery process.
		// Publishing applications use that metadata to decide whether to send to
		// this application or not.  
		VideoSubscriberInterface videoInterface(xmlFiles, videoMetadata, 
			multicastVideoData);

		bool isDone = false;

		// Create the video display handler that actually shows the video 
		VideoDisplayHandler *videoDisplay = new VideoDisplayHandler(vout, &isDone);

		// Register the display handler with the DataReader that will notify it
		// when video frames arrive 
		videoInterface.GetVideoStreamReader()->RegisterVideoHandler(videoDisplay);

		// Continue while the video is not finished.
		while (!isDone) 
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
		"    --multicast" <<
		"          Use multicast for streaming video" 
		<< endl;
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
