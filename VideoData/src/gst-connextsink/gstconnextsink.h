/*
 * (c) 2023 Copyright, Real-Time Innovations, Inc. (RTI) All rights reserved.
 *
 * RTI grants Licensee a license to use, modify, compile, and create derivative
 * works of the software.  Licensee may
 * redistribute copies of the software provided that all such copies are
 * subject to this license. The software is provided "as is", with no warranty
 * of any type, including any warranty for fitness for any purpose. RTI is
 * under no obligation to maintain or support the software.  RTI shall not be
 * liable for any incidental or consequential damages arising out of the use or
 * inability to use the software.
 */

#ifndef _GST_CONNEXTSINK_H_
#define _GST_CONNEXTSINK_H_

#include <gst/video/gstvideosink.h>
#include <gst/video/video.h>
#include <stdio.h>

#include "video.h"
#include "videoSupport.h"

G_BEGIN_DECLS

#define GST_TYPE_CONNEXT_SINK (gst_connextsink_get_type())
#define GST_CONNEXT_SINK(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_CONNEXT_SINK, GstConnextSink))
#define GST_CONNEXTSINK_CLASS(class) (G_TYPE_CHECK_CLASS_CAST((class), GST_TYPE_CONNEXT_SINK, GstConnextSinkClass))
#define GST_IS_CONNEXT_SINK(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_CONNEXT_SINK))
#define GST_IS_CONNEXTSINK_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE((class), GST_TYPE_CONNEXT_SINK))

typedef struct GstConnextSink_Context GstConnextSink_Context;
typedef struct GstConnextSink GstConnextSink;
typedef struct GstConnextSinkClass GstConnextSinkClass;

/* Contains the Connext DDS entities used to publish the data from a GStreamer pipeline*/
struct GstConnextSink_Context
{
	DDS_DomainParticipant* participant;			
	DDS_Publisher* publisher;					
	DDS_Topic* topic;							
	DDS_DataWriter* writer;						
	Video_StreamDataWriter* videostream_writer;	
	Video_Stream* instance;						
	DDS_InstanceHandle_t instance_handle;		
	uint32_t domainId;							
	gchar* topicName;							
	gchar* key;									
	gchar* dpQosProfile;						
	gchar* dwQosProfile;						
	uint32_t numberFramesSent;					
	gsize accumulatedFrameSize;					
	uint32_t printFrameSize;					
};

struct GstConnextSink
{
	GstVideoSink base_connextsink;
	GstConnextSink_Context connext;
};

struct GstConnextSinkClass
{
	GstVideoSinkClass base_connextsink_class;
};

GType gst_connextsink_get_type(void);

G_END_DECLS

#endif  //_GST_ConnextSINK_H_
