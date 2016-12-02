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
#ifndef VIDEOOUTPUT_H_
#define VIDEOOUTPUT_H_

#include <gst/gst.h>
#include <gst/app/gstappsrc.h>

#include "VideoBuffer.h"
#include "VideoEvent.h"

#include <string>

// ----------------------------------------------------------------------------
//
// EMDSVideoOutput:
//
// Base class for classes that can process incoming video data.  This includes
// classes that display video, or trace that video frames have arrived.
//
class EMDSVideoOutput
{
public:
	// --- Constructor --- 
	EMDSVideoOutput();

	// --- Initialization --- 
	virtual void Initialize();

	virtual void PushFrame(EMDSBuffer *buffer); 

	// --- getters and setters ---
	EMDSFrameHandler *GetFrameHandler()
	{
		return _frameHandler;
	}


protected:
	EMDSFrameHandler *_frameHandler;
	GstPipeline *_save_pipeline;
};


// ----------------------------------------------------------------------------
//
// EMDSVideoDisplayOutput:
//
// Class that receives video data and displays it.
//
class EMDSVideoDisplayOutput : public EMDSVideoOutput
{
public:
	// --- Constructor --- 
	EMDSVideoDisplayOutput();

	// --- Initialization --- 
	virtual void Initialize();

	// --- Get the metadata about the stream in a string format --- 
	std::string GetStreamMetadata();

	// --- getters and setters --- 
	GstPipeline *GetDisplayPipeline()
	{
		return _displayPipeline;
	}

protected:
	GstPipeline *_displayPipeline;
};



//-----------------------------------------------------------------------------
//
// DisplayFrameHandler:
//
// Class that receives callbacks from the video display output class, and 
// updates the gstreamer framework that a new frame has arrived.
//
class DisplayFrameHandler : public EMDSFrameHandler
{ 
public:

	// --- Constructor --- 
	DisplayFrameHandler(EMDSVideoDisplayOutput *output)
	{
		_displayOutput = output;
		_appSrc = NULL;
	}

	// 
	// This function is a callback that receives a notification that video data is 
	// available, and sends that data through the gstreamer interfaces to be 
	// decoded and displayed by the other plugins in the pipeline
	//
	virtual void FrameReady(void *obj, EMDSBuffer *buffer)
	{
		GstBuffer *appbuffer = NULL;

		if(_appSrc == NULL)
		{
			// Initialize the app source.
			_appSrc = 
				(GstAppSrc*)gst_bin_get_by_name(
					(GstBin*)_displayOutput->GetDisplayPipeline(),
					"src");
		}

		// Allocate a new buffer from the GStreamer framework that will be
		// used to display this video frame.
		appbuffer = 
			gst_buffer_new_wrapped(buffer->GetData(), 
				buffer->GetSize());

		// The buffer becomes managed by the GStreamer framework as soon as
		// we push it, so we do not have to free it.

		gst_app_src_push_buffer(_appSrc, appbuffer);

	}

	virtual void EOSHandler(void *obj, EMDSBuffer *buffer)
	{
	}

	EMDSVideoDisplayOutput *_displayOutput;
	GstAppSrc *_appSrc;
};



//-----------------------------------------------------------------------------
//
// EMDSVideoTraceOutput:
//
// Class for debugging traces of video output.  Currently only supported on 
// Linux
//
#ifndef WIN32
class EMDSVideoTraceOutput : public EMDSVideoOutput
{
public:
	// --- Constructor --- 
	EMDSVideoTraceOutput(std::string path);

	// --- Because this is for debug only, leave public --- 
	int _fd;
	char *_filepath;
};
#endif


#endif /* VIDEOOUPUT_H_ */
