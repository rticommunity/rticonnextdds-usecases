/* --------------------------------------------
Copyright (c) 2013, University of Granada
Copyright (c) 2013, Real-Time Innovations, Inc.
Copyright (c) 2013, Javier Povedano-Molina
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notices, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notices,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the copyright holders or contributors.

This work was partially completed at the University of Granada under funding by 
Real-Time Innovations, Inc. (RTI).  The above license is granted with
 the permission of RTI.

-------------------------------------------- */
#include <iostream>
#include <sstream>
#include "VideoSource.h"
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#ifdef WIN32
#include <gst/app/gstappbuffer.h>
#endif
#include "../Generated/VideoData.h"

static int seqn = 0;

// ----------------------------------------------------------------------------
// 
// Function passed into the video source thread.  This pulls the buffer from
// the provider (from the GStreamer framework) and notifies the frame 
// ready handler that there is a frame available.
//
void *video_source_worker(void *src)
{

	EMDSVideoSource *videoSource = (EMDSVideoSource *)src;
	static unsigned char data[com::media::generated::MAX_BUFFER_SIZE];

	if (videoSource->GetFrameReadyHandler() == NULL)
	{
		std::cout << "Callback handler is NULL" << std::endl;
		return NULL;
	}

	while (1)
	{
#ifdef WIN32
		GstBuffer * buffer =
			gst_app_sink_pull_buffer((GstAppSink *)videoSource->GetAppSink());
#else
		GstBuffer * buffer = gst_sample_get_buffer(gst_app_sink_pull_sample((GstAppSink*)videoSource->GetAppSink()));
#endif		
		if (buffer == NULL)
		{
			return NULL;
		}

#ifdef WIN32
		if (GST_BUFFER_SIZE(buffer) >
			com::media::generated::MAX_BUFFER_SIZE)
		{
			std::cout << "Buffer is larger than the max buffer size"
				<< std::endl;
	}
		EMDSBuffer *emdsBuffer
			= new EMDSBuffer(GST_BUFFER_SIZE(buffer));

		emdsBuffer->SetData(GST_BUFFER_DATA(buffer),
			GST_BUFFER_SIZE(buffer));

#else

		EMDSBuffer *emdsBuffer
			= new EMDSBuffer(gst_buffer_get_size(buffer));

		
		int s = gst_buffer_extract(buffer, 0, data, gst_buffer_get_size(buffer));

		emdsBuffer->SetData(&data[0], gst_buffer_get_size(buffer));
#endif

		emdsBuffer->SetSeqn(seqn);

		seqn++;

		videoSource->GetFrameReadyHandler()->FrameReady(
			videoSource->GetHandlerObj(), emdsBuffer);

		delete emdsBuffer;
	}

	return NULL;

}

// ----------------------------------------------------------------------------
// Video source constructor
EMDSVideoSource::EMDSVideoSource(std::string url)
{

	if (url.empty())
	{
 		std::cout << "Video Source: Creating source from 'null' url" 
			<< std::endl;
 		return;
 	}

	_url = url;

	_appSink = NULL;
	_handlerObj = NULL;
	_worker = NULL;
 	_frameReadyHandler = NULL;
	_videoEncodingPipeline = NULL;

}

// ----------------------------------------------------------------------------
//
// Function to pass into a GStreamer API to connect up the matroska demux
// with an application sink.
//
static void EMDSVideoSource_detect_new_pad(GstElement *element, GstPad *pad, 
	gpointer data)
{
	// May be muxer or may be appSink depending on platform
	GstElement *linkElement = (GstElement *)data;
	GstPad *sinkPad = NULL;

	if (0 == strncmp(gst_pad_get_name(pad), "video", 5))
	{
		// Link the sink pad of the muxer to the pad of the demux
#ifdef WIN32_MUX
		sinkPad = gst_element_get_request_pad(linkElement, "video_%d");
#else
		sinkPad = gst_element_get_static_pad(linkElement, "sink");
#endif

		if (GST_PAD_LINK_FAILED(gst_pad_link(pad, sinkPad)))
		{
			std::cout << "Failed to link the decoder and the app sink" 
				<< std::endl;
		}

		gst_element_set_state(linkElement, GST_STATE_PLAYING);
		gst_object_unref(sinkPad);

	}

}

// ----------------------------------------------------------------------------
//
// Initialize the GStreamer video pipeline
//
int EMDSVideoSource::Initialize()
{
	int retcode = 0;

	// First call to initialize the GStreamer framework
	gst_init(NULL, NULL);

	// Create the pipeline
	_videoEncodingPipeline = 
		GST_PIPELINE(gst_pipeline_new("video_source_pipeline"));

	if (_videoEncodingPipeline == NULL)
	{
		std::cout << "Error creating video pipeline" << std::endl;
		return -1;
	}

	// Create a file source that will load the file pointed to by the URL
	GstElement *source = gst_element_factory_make("filesrc", "filesrc");
	if (source == NULL)
	{
		std::cout << "Error creating file source" << std::endl;
		return -1;
	}

	// Set the location 
	g_object_set(source, "location", _url.c_str(), NULL);

	// Create a matroska demux
	GstElement *demux = gst_element_factory_make("matroskademux", "demux");
	if (demux == NULL)
	{
		std::cout << "Error creating demux" << std::endl;
		return -1;
	}

	// Add the source and demux to the pipeline
	gst_bin_add_many(GST_BIN (_videoEncodingPipeline), 
		source, demux, NULL);

#ifdef WIN32_MUX
	// Add muxer that takes the inputs from the demux
	GstElement *muxer = gst_element_factory_make("matroskamux", "muxer");
	if (muxer == NULL)
	{
		std::cout << "Error creating muxer" << std::endl;
		return -1;
	}

	gst_bin_add(GST_BIN (_videoEncodingPipeline), muxer);

	// Set muxer's property to streamable
	g_object_set(muxer, "streamable", TRUE, NULL);

#endif

	// Application sink -> takes data from gstreamer and gives it to the
	// RTI Connext publisher
	_appSink = gst_element_factory_make("appsink", "appsink");
	if (_appSink == NULL)
	{
		std::cout << "Failed to create appSink" << std::endl;
		return -1;
	}

	// Add the appSink to the pipeline
	gst_bin_add(GST_BIN (_videoEncodingPipeline), _appSink);

	// Listen for the pad-added so we can dynamically link the 
	// demuxer to the app sink, if it is video data (not audio or subtitles)
#ifdef WIN32_MUX
	if (!g_signal_connect(demux, "pad-added", 
		G_CALLBACK (EMDSVideoSource_detect_new_pad), muxer))
#else
	if (!g_signal_connect(demux, "pad-added", 
		G_CALLBACK (EMDSVideoSource_detect_new_pad), _appSink))
#endif
	{
		std::cout << "Failed to connect signal" << std::endl;
		return -1;
	}

	// Link the source and the demuxer
	if (!gst_element_link(source, demux))
	{
		std::cout << "Failed to link file source and matraoskademux"
			<< std::endl;
		return -1;
	}

#ifdef WIN32_MUX
	// Link the muxer and the app sink
	if (!gst_element_link(muxer, _appSink))
	{
		std::cout << "Failed to link muxer and appsink" << std::endl;
		return -1;
	}
#endif 

	// Enable the pipeline.
	// This typically fails when the URL does not point to a valid file.
	if (GST_STATE_CHANGE_FAILURE == 
		gst_element_set_state(GST_ELEMENT (_videoEncodingPipeline), 
		GST_STATE_PLAYING))
	{
		std::cout << "Failed to create the video source.  " 
			<< "Is the file path correct?" << std::endl;
		std::cout << "File path: " << _url.c_str() << std::endl;
		return -1;
	}

	return 0;
}

// ----------------------------------------------------------------------------
//
// Get my own pipeline capabilities.
//
std::string EMDSVideoSource::GetStreamMetadata()
{
	GstPad *sinkPad = gst_element_get_static_pad(_appSink, "sink");
	GstCaps *caps = gst_pad_get_allowed_caps(sinkPad);
	char *capsStr = gst_caps_to_string(caps);
	return capsStr;
}

// ----------------------------------------------------------------------------
//
// Compare whether my pipeline capabilities are compatible with a remote 
// pipeline's capabilities.
//
bool EMDSVideoSource::IsMetadataCompatible(
	std::string subscriberMetadata)
{
	GstCaps *sourceCaps = gst_caps_from_string(
		GetStreamMetadata().c_str());
	GstCaps *sinkCaps = gst_caps_from_string(
		subscriberMetadata.c_str());
	return (bool)gst_caps_is_always_compatible(
		sourceCaps,
		sinkCaps);
}

// ----------------------------------------------------------------------------
//
// Start the video source thread
//
int EMDSVideoSource::Start()
{
	std::cout << "Initializing and starting video source" << std::endl;

	// Create video thread
	_worker = new OSThread(video_source_worker, (void *)this);

	if (_worker == NULL)
	{
		std::cout << "Failed to create video thread" << std::endl;
		return -1;
	}

	// Start video thread
	_worker->Run();

	std::cout << "Video Source: VideoSource started" << std::endl;

	return 0;
}

// ----------------------------------------------------------------------------
//
// Attach a class that will handle the notification that a frame is ready to be
// processed.
//
void EMDSVideoSource::SetNewFrameCallbackHandler(
			EMDSFrameHandler *frameReadyHandler, void *obj)
{
	_frameReadyHandler = frameReadyHandler;
	_handlerObj = obj;
}


