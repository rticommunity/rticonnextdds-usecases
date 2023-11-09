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

#ifndef _GST_CONNEXTSRC_H_
#define _GST_CONNEXTSRC_H_

#include <gst/base/gstpushsrc.h>

#include "video.h"
#include "videoSupport.h"

G_BEGIN_DECLS

#define GST_TYPE_CONNEXTSRC (gst_connextsrc_get_type())
#define GST_CONNEXTSRC(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_CONNEXTSRC, GstConnextSrc))
#define GST_CONNEXTSRC_CLASS(class) (G_TYPE_CHECK_CLASS_CAST((class), GST_TYPE_CONNEXTSRC, GstConnextSrcClass))
#define GST_IS_CONNEXTSRC(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_CONNEXTSRC))
#define GST_IS_CONNEXTSRC_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE((class), GST_TYPE_CONNEXTSRC))

typedef struct GstConnextSrc_Context GstConnextSrc_Context;
typedef struct GstConnextSrc GstConnextSrc;
typedef struct GstConnextSrcClass GstConnextSrcClass;

/* Contains the Connext DDS entities used to receive the data fed into the GStreamer pipeline */
struct GstConnextSrc_Context
{
	DDS_DomainParticipant* participant;				
	DDS_Subscriber* subscriber;						
	DDS_Topic* topic;								
	struct DDS_DataReaderListener reader_listener;	
	DDS_DataReader* reader;							
	Video_StreamDataReader* videoStream_reader;		
	uint32_t domainId;								
	gchar* topicName;								
	gchar* key;										
	gchar* dpQosProfile;							
	gchar* drQosProfile;							
	gchar* prevKey;									
	DDS_ContentFilteredTopic* cft;					
	struct DDS_StringSeq cft_parameters;			
	GstBuffer* frame_buffer;						
};

struct GstConnextSrc
{
	GstPushSrc base_connextsrc;
	GstConnextSrc_Context connext;
	/* Queue in which Connext frames are placed in the on_data_available callback */
	GAsyncQueue* g_filled_frame_queue;
};

struct GstConnextSrcClass
{
	GstPushSrcClass base_connextsrc_class;
};

GType gst_connextsrc_get_type(void);

G_END_DECLS

#endif
