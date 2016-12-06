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

#ifndef VIDEOSOURCE_H_
#define VIDEOSOURCE_H_

#include <map>
#include <string>
#include "VideoEvent.h"
#include "OSAPI.h"


#include <gst/gst.h>

struct EMDSVideoStreamSettings 
{
        char *codec;
        unsigned int width;
        unsigned int height;
        unsigned int bitrate;
        double fps;
};

// ------------------------------------------------------------------------- //
// 
// EMDSVideoSource:
//
// Sets up a video pipeline, and receives video frames from the GStreamer 
// framework.  
// 
// If a callback is registered using the SetNewFrameCallbackHandler call, this
// will call back that handler when a new frame becomes available.
// 
// ------------------------------------------------------------------------- //
class EMDSVideoSource 
{
public:

	// --- Constructor --- 
	EMDSVideoSource(std::string url);

	// --- Initialization --- 
	int Initialize();

	// --- Get Stream Metadata
	// This method queries information about the video stream, such as codec,
	// FPS, and whatever else is available.  It returns this information in 
	// a comma-separated string format.  This format is readable by the 
	// gstreamer framework
	std::string GetStreamMetadata();

	// --- Is metadata compatible?
	// Check if a string representing the stream metadata for a video receiver
	// is compatible with the formats supported by this source.
	bool IsMetadataCompatible(std::string metadata);


	// --- Start ---
	int Start();

	// --- Set Frame Callback Handler
	void SetNewFrameCallbackHandler(EMDSFrameHandler *handler, void *obj);

	// --- Getters and setters
	EMDSFrameHandler *GetFrameReadyHandler()
	{
		return _frameReadyHandler;
	}

	void *GetHandlerObj() 
	{
		return _handlerObj;
	}

   GstPipeline *GetPipeline()
   {
      return _videoEncodingPipeline;
   }

	GstElement *GetAppSink()
	{
		return _appSink;
	}

private:


	// --- Private members --- 

	// File path to open
	std::string _url;
	OSThread *_worker;
	EMDSFrameHandler *_frameReadyHandler;
	void *_handlerObj;

	// GStreamer objects
	GstPipeline *_videoEncodingPipeline;
	GstElement *_appSink;

};



#endif /* VIDEOSOURCE_H_ */
