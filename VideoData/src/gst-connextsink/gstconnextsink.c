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

#include <gst/gst.h>
#include <gst/video/gstvideosink.h>
#include <gst/video/video.h>
#include <stdio.h>
#include <string.h>

#include "gstconnextsink.h"

GST_DEBUG_CATEGORY_STATIC(gst_connextsink_debug_category);
#define GST_CAT_DEFAULT gst_connextsink_debug_category
#define PRINT_SIZE_EVERY_X_FRAMES 50
#define PROFILE_NAME_MAX_LEN 200

/* prototypes */
/* set gstreamer property */
static void gst_connextsink_set_property(GObject* object, guint property_id, const GValue* value, GParamSpec* pspec);

/* get gstreamer property */
static void gst_connextsink_get_property(GObject* object, guint property_id, GValue* value, GParamSpec* pspec);

/* dispose connextsink */
static void gst_connextsink_dispose(GObject* object);

/* finalize connext sink */
static void gst_connextsink_finalize(GObject* object);

/* write frame to connext */
static GstFlowReturn gst_connextsink_show_frame(GstVideoSink* video_sink, GstBuffer* buf);

/* parse qos profiles */
static int gst_connextsink_get_qos_library_profile(GstConnextSink* connextsink, gchar* qosProfile, char* qos_library_name, char* qos_profile_name);

/* initialize publisher */
static int gst_connextsink_publisher_init(GstConnextSink* connextsink);

/* shutdown publisher */
static int gst_connextsink_publisher_shutdown(DDS_DomainParticipant* participant);

/* element methods */
static GstStateChangeReturn gst_connextsink_change_state(GstElement* element, GstStateChange transition);

#define DEFAULT_QOS "BuiltinQosLibExp::Generic.StrictReliable"

enum
{
	PROP_0,
	PROP_CONNEXT_DOMAIN_ID,
	PROP_CONNEXT_TOPIC,
	PROP_CONNEXT_KEY,
	PROP_CONNEXT_DP_QOS_PROFILE,
	PROP_CONNEXT_DW_QOS_PROFILE,
	PROP_CONNEXT_PRINT_FRAME_SIZE
};

#define CONNEXTSINK_VIDEO_CAPS                                        \
	GST_VIDEO_CAPS_MAKE(GST_VIDEO_FORMATS_ALL)                    \
	";"                                                           \
	"video/x-raw, format=(string) { bggr, rggb, grbg, gbrg }, "   \
	"width = " GST_VIDEO_SIZE_RANGE ", "                          \
	"height = " GST_VIDEO_SIZE_RANGE ", "                         \
	"framerate = " GST_VIDEO_FPS_RANGE ";"                        \
	"video/x-h264, stream-format=(string) { avc, byte-stream }, " \
	"width = " GST_VIDEO_SIZE_RANGE ", "                          \
	"height = " GST_VIDEO_SIZE_RANGE ", "                         \
	"framerate = " GST_VIDEO_FPS_RANGE

/* pad template */
static GstStaticPadTemplate gst_connextsink_sink_template =
    GST_STATIC_PAD_TEMPLATE("sink", GST_PAD_SINK, GST_PAD_ALWAYS, GST_STATIC_CAPS_ANY);

/* class initialisation */
G_DEFINE_TYPE_WITH_CODE(
    GstConnextSink,
    gst_connextsink,
    GST_TYPE_VIDEO_SINK,
    GST_DEBUG_CATEGORY_INIT(gst_connextsink_debug_category, "connextsrc", 0, "debug category for connextsrc element"))

static void gst_connextsink_class_init(GstConnextSinkClass* class)
{
	GObjectClass* gobject_class = G_OBJECT_CLASS(class);
	GstElementClass* element_class = GST_ELEMENT_CLASS(class);
	GstVideoSinkClass* video_sink_class = GST_VIDEO_SINK_CLASS(class);

	/* Setting up pads and setting metadata should be moved to
	 base_class_init if you intend to subclass this class. */
	gst_element_class_add_pad_template(GST_ELEMENT_CLASS(class),
	                                   gst_static_pad_template_get(&gst_connextsink_sink_template));

	gst_element_class_set_static_metadata(GST_ELEMENT_CLASS(class),
	                                      "Connext VideoStream Sink",
	                                      "Sink/Network",
	                                      "Send data over networks using Connext middleware",
	                                      "RTI <community@rti.com>");

	gobject_class->set_property = gst_connextsink_set_property;
	gobject_class->get_property = gst_connextsink_get_property;
	gobject_class->dispose = gst_connextsink_dispose;
	gobject_class->finalize = gst_connextsink_finalize;
	video_sink_class->show_frame = GST_DEBUG_FUNCPTR(gst_connextsink_show_frame);

	element_class->change_state = gst_connextsink_change_state;

	/* define properties */
	g_object_class_install_property(
			gobject_class,
			PROP_CONNEXT_DOMAIN_ID,
			g_param_spec_uint(
					"domain", "Connext domain ID", "The Domain ID used for the Connext publisher", 0, 231, 0, G_PARAM_READWRITE));

	g_object_class_install_property(
			gobject_class,
			PROP_CONNEXT_TOPIC,
			g_param_spec_string(
					"topic", "Connext Topic", "The topic name to publish on the Connext network", NULL, G_PARAM_READWRITE));

	g_object_class_install_property(
			gobject_class,
			PROP_CONNEXT_KEY,
			g_param_spec_string(
					"key", "Connext Topic Key", "The topic key to publish on the Connext network", NULL, G_PARAM_READWRITE));

	g_object_class_install_property(
			gobject_class,
			PROP_CONNEXT_DP_QOS_PROFILE,
			g_param_spec_string(
					"dp-qos-profile",
					"Connext DP Qos Profile",
					"Default QoS profile used when creating the DP of this sink element",
					DEFAULT_QOS,
					G_PARAM_READWRITE));

	g_object_class_install_property(
			gobject_class,
			PROP_CONNEXT_DW_QOS_PROFILE,
			g_param_spec_string(
					"dw-qos-profile",
					"Connext DW Qos Profile",
					"Default QoS profile used when creating the DW of this sink element",
					DEFAULT_QOS,
					G_PARAM_READWRITE));
	
	g_object_class_install_property(
			gobject_class,
			PROP_CONNEXT_PRINT_FRAME_SIZE,
			g_param_spec_uint(
					"print-frame-size",
					"Print size of frame",
					"Print average frame size every 50 frames. Default: 0",
					0, /* minimum */ 
					1, /* maximum */ 
					0, /* default */ 
					G_PARAM_READWRITE));
}

static void gst_connextsink_init(GstConnextSink* connextsink)
{
	connextsink->connext.domainId = 0;
	connextsink->connext.topicName = NULL;
	connextsink->connext.key = g_strdup("");
	connextsink->connext.instance_handle = DDS_HANDLE_NIL;
	connextsink->connext.dpQosProfile = g_strdup(DEFAULT_QOS);
	connextsink->connext.dwQosProfile = g_strdup(DEFAULT_QOS);
	connextsink->connext.numberFramesSent = 0;
	connextsink->connext.printFrameSize = 0;

	GST_INFO_OBJECT(connextsink, "connextsink initialization complete.");
}

void gst_connextsink_set_property(GObject* object, guint property_id, const GValue* value, GParamSpec* pspec)
{
	GstConnextSink* connextsink = GST_CONNEXT_SINK(object);

	GST_DEBUG_OBJECT(connextsink, "set_property");

	switch (property_id)
	{
		case PROP_CONNEXT_DOMAIN_ID: connextsink->connext.domainId = g_value_get_uint(value); break;
		case PROP_CONNEXT_TOPIC:
		{
			g_free(connextsink->connext.topicName);
			connextsink->connext.topicName = g_value_dup_string(value);
			break;
		}
		case PROP_CONNEXT_KEY:
		{
			g_free(connextsink->connext.key);
			connextsink->connext.key = g_value_dup_string(value);
			break;
		}
		case PROP_CONNEXT_DP_QOS_PROFILE:
		{
			g_free(connextsink->connext.dpQosProfile);
			connextsink->connext.dpQosProfile = g_value_dup_string(value);
			break;
		}
		case PROP_CONNEXT_DW_QOS_PROFILE:
		{
			g_free(connextsink->connext.dwQosProfile);
			connextsink->connext.dwQosProfile = g_value_dup_string(value);
			break;
		}
		case PROP_CONNEXT_PRINT_FRAME_SIZE:
		{
			connextsink->connext.printFrameSize = g_value_get_uint(value);
			break;
		}
		default: G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec); break;
	}
}

void gst_connextsink_get_property(GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
	GstConnextSink* connextsink = GST_CONNEXT_SINK(object);

	GST_DEBUG_OBJECT(connextsink, "get_property");

	switch (property_id)
	{
		case PROP_CONNEXT_DOMAIN_ID: g_value_set_uint(value, connextsink->connext.domainId); break;
		case PROP_CONNEXT_TOPIC: g_value_set_string(value, connextsink->connext.topicName); break;
		case PROP_CONNEXT_KEY: g_value_set_string(value, connextsink->connext.key); break;
		case PROP_CONNEXT_DP_QOS_PROFILE: g_value_set_string(value, connextsink->connext.dpQosProfile); break;
		case PROP_CONNEXT_DW_QOS_PROFILE: g_value_set_string(value, connextsink->connext.dwQosProfile); break;
		case PROP_CONNEXT_PRINT_FRAME_SIZE: g_value_set_uint(value, connextsink->connext.printFrameSize); break;
		default: G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec); break;
	}
}

static GstStateChangeReturn gst_connextsink_change_state(GstElement* element, GstStateChange transition)
{
	GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
	GstConnextSink* connextsink = GST_CONNEXT_SINK(element);
	switch (transition)
	{
		case GST_STATE_CHANGE_NULL_TO_READY:
			{
				if (connextsink->connext.topicName == NULL)
				{
					GST_ERROR("\nConnext topic not specified in the pipeline. Cannot continue!\n\n");
					return GST_STATE_CHANGE_FAILURE;
				}
				char msg[300];
				snprintf(msg, sizeof(msg),
				        "Domain ID is %d; Topic is '%s' with key '%s', DP QoS is '%s' and DW QoS is '%s'",
				        connextsink->connext.domainId,
				        connextsink->connext.topicName,
				        connextsink->connext.key,
				        connextsink->connext.dpQosProfile,
						connextsink->connext.dwQosProfile);
				printf("%s\n", msg);
				GST_INFO_OBJECT(connextsink, "%s", msg);

				if (gst_connextsink_publisher_init(connextsink))
				{
					return GST_STATE_CHANGE_FAILURE;
				}
				break;
			}
		default: break;
	}

	ret = GST_ELEMENT_CLASS(gst_connextsink_parent_class)->change_state(element, transition);

	return ret;
}

void gst_connextsink_dispose(GObject* object)
{
	GstConnextSink* connextsink = GST_CONNEXT_SINK(object);

	GST_DEBUG_OBJECT(connextsink, "dispose");

	/* clean up. may be called multiple times */
	Video_StreamTypeSupport_delete_data(connextsink->connext.instance);
	
	if (gst_connextsink_publisher_shutdown(connextsink->connext.participant))
	{
		GST_ERROR("Failed to shutdown Connext publisher cleanly!");
	}

	G_OBJECT_CLASS(gst_connextsink_parent_class)->dispose(object);
}

void gst_connextsink_finalize(GObject* object)
{
	GstConnextSink* connextsink = GST_CONNEXT_SINK(object);

	GST_DEBUG_OBJECT(connextsink, "finalize");

	/* clean up object here */
	G_OBJECT_CLASS(gst_connextsink_parent_class)->finalize(object);
}

static GstFlowReturn gst_connextsink_show_frame(GstVideoSink* sink, GstBuffer* buf)
{
	GstMapInfo mapInfo;
	DDS_ReturnCode_t retcode;
	GstConnextSink* connextsink = GST_CONNEXT_SINK(sink);

	GST_DEBUG_OBJECT(connextsink, "copying gst frame to Connext data container");

	gst_buffer_map(buf, &mapInfo, GST_MAP_READ);

	/* loan the gstreamer buffer to Connext */
	if(!DDS_OctetSeq_loan_contiguous(&connextsink->connext.instance->frame, (DDS_Octet*)mapInfo.data, mapInfo.size, mapInfo.size))
	{
		GST_ERROR_OBJECT(connextsink, "unable to loan buffer to Connext");
		gst_buffer_unmap(buf, &mapInfo);
		return GST_FLOW_ERROR;
	}

	connextsink->connext.numberFramesSent++;
	connextsink->connext.accumulatedFrameSize += mapInfo.size;
	if (connextsink->connext.printFrameSize && (connextsink->connext.numberFramesSent % PRINT_SIZE_EVERY_X_FRAMES == 0))
	{
		printf(
				"Average size of frames: %lu\n",
				connextsink->connext.accumulatedFrameSize / PRINT_SIZE_EVERY_X_FRAMES);
		connextsink->connext.accumulatedFrameSize = 0;
	}

	GST_LOG_OBJECT(connextsink, "publishing frame via Connext, %ld Bytes", mapInfo.size);
	/* Key is already in the sample object due to publisher_init() */
	/* write the data */
	retcode = Video_StreamDataWriter_write(
			connextsink->connext.videostream_writer,
			connextsink->connext.instance,
			&connextsink->connext.instance_handle);
	if (retcode != DDS_RETCODE_OK)
	{
		GST_ERROR_OBJECT(connextsink, "write error %d", retcode);
		gst_buffer_unmap(buf, &mapInfo);
		return GST_FLOW_ERROR;
	}

	/* return loan and unmap the gstreamer buffer */
	if(!DDS_OctetSeq_unloan(&connextsink->connext.instance->frame))
	{
		GST_ERROR_OBJECT(connextsink, "unable to return buffer to Gstreamer");
		gst_buffer_unmap(buf, &mapInfo);
		return GST_FLOW_ERROR;
	}
	gst_buffer_unmap(buf, &mapInfo);

	return GST_FLOW_OK;
}

static int gst_connextsink_get_qos_library_profile(GstConnextSink* connextsink, gchar* qosProfile, char* qos_library_name, char* qos_profile_name)
{	
	if(strlen(qosProfile) >= PROFILE_NAME_MAX_LEN){
		GST_ERROR_OBJECT(connextsink, "QoS profile string is too long: %s", qosProfile);
		return 1;
	}

	char str[PROFILE_NAME_MAX_LEN];
	strcpy(str, qosProfile);

	const char* delim = "::";
	const char* token = strtok(str, delim);

	if (token != NULL)
	{
		strcpy(qos_library_name, token);
	}
	else
	{
		GST_ERROR_OBJECT(connextsink, "Cannot parse provided QoS profile string: %s", qosProfile);
		return 1;
	}

	token = strtok(NULL, delim);
	if (token != NULL)
	{
		strcpy(qos_profile_name, token);
	}
	else
	{
		GST_ERROR_OBJECT(connextsink, "Cannot parse provided QoS profile string: %s", qosProfile);
		return 1;
	}
	return 0;
}

static int gst_connextsink_publisher_init(GstConnextSink* connextsink)
{
	char dpQosLib[PROFILE_NAME_MAX_LEN];
	char dpQosProfile[PROFILE_NAME_MAX_LEN];
	char dwQosLib[PROFILE_NAME_MAX_LEN];
	char dwQosProfile[PROFILE_NAME_MAX_LEN];

	int parse_ret = gst_connextsink_get_qos_library_profile(connextsink, connextsink->connext.dpQosProfile, dpQosLib, dpQosProfile);
	if (parse_ret)
	{
		return 1;
	}
	parse_ret = gst_connextsink_get_qos_library_profile(connextsink, connextsink->connext.dwQosProfile, dwQosLib, dwQosProfile);
	if (parse_ret)
	{
		return 1;
	}

	DDS_ReturnCode_t retcode = DDS_DomainParticipantFactory_set_default_participant_qos_with_profile(
	    DDS_TheParticipantFactory, dpQosLib, dpQosProfile);
	if (retcode != DDS_RETCODE_OK)
	{
		GST_ERROR_OBJECT(connextsink, "error %d; cannot set partipant qos to %s::%s", retcode, dpQosLib, dpQosProfile);
		return 1;
	}

	connextsink->connext.participant = DDS_DomainParticipantFactory_create_participant_with_profile(
	    DDS_TheParticipantFactory, connextsink->connext.domainId, dpQosLib, dpQosProfile, NULL, DDS_STATUS_MASK_NONE);
	if (connextsink->connext.participant == NULL)
	{
		GST_ERROR_OBJECT(connextsink, "create_participant error");
		return 1;
	}

	connextsink->connext.publisher = DDS_DomainParticipant_create_publisher(
	    connextsink->connext.participant, &DDS_PUBLISHER_QOS_DEFAULT, NULL, DDS_STATUS_MASK_NONE);
	if (connextsink->connext.publisher == NULL)
	{
		GST_ERROR_OBJECT(connextsink, "create_publisher error %d", retcode);
		return 1;
	}

	const char* type_name = Video_StreamTypeSupport_get_type_name();
	retcode = Video_StreamTypeSupport_register_type(connextsink->connext.participant, type_name);
	if (retcode != DDS_RETCODE_OK)
	{
		GST_ERROR_OBJECT(connextsink, "register_type error %d", retcode);
		return 1;
	}

	connextsink->connext.topic = DDS_DomainParticipant_create_topic(
	    connextsink->connext.participant, connextsink->connext.topicName, type_name, &DDS_TOPIC_QOS_DEFAULT, NULL, DDS_STATUS_MASK_NONE);
	if (connextsink->connext.topic == NULL)
	{
		GST_ERROR_OBJECT(connextsink, "create_topic error");
		return 1;
	}

	connextsink->connext.writer = DDS_Publisher_create_datawriter_with_profile(
	    connextsink->connext.publisher, connextsink->connext.topic, dwQosLib, dwQosProfile, NULL, DDS_STATUS_MASK_NONE);
	if (connextsink->connext.writer == NULL)
	{
		GST_ERROR_OBJECT(connextsink, "create_datawriter error");
		return 1;
	}

	connextsink->connext.videostream_writer = Video_StreamDataWriter_narrow(connextsink->connext.writer);
	if (connextsink->connext.videostream_writer == NULL)
	{
		GST_ERROR_OBJECT(connextsink, "DataWriter_narrow error");
		return 1;
	}

	connextsink->connext.instance = Video_StreamTypeSupport_create_data_ex(DDS_BOOLEAN_TRUE);
	if (connextsink->connext.instance == NULL)
	{
		GST_ERROR_OBJECT(connextsink, "VideoStreamTypeSupport_create_data error");
		return 1;
	}

	connextsink->connext.instance->id = connextsink->connext.key;
	connextsink->connext.instance_handle = Video_StreamDataWriter_register_instance(
			connextsink->connext.videostream_writer,
			connextsink->connext.instance);
	if(DDS_InstanceHandle_equals(&connextsink->connext.instance_handle, &DDS_HANDLE_NIL))
	{
		GST_ERROR_OBJECT(connextsink, "Video_StreamDataWriter_register_instance error");
		return 1;
	}

	if(!DDS_OctetSeq_initialize(&connextsink->connext.instance->frame))
	{
		GST_ERROR_OBJECT(connextsink, "frame sequence initialize error");
		return 1;
	}

	return 0;
}

static int gst_connextsink_publisher_shutdown(DDS_DomainParticipant* participant)
{
	DDS_ReturnCode_t retcode;
	GST_INFO("Calling Connext publisher shut down\n");

	if (participant != NULL)
	{
		retcode = DDS_DomainParticipant_delete_contained_entities(participant);
		if (retcode != DDS_RETCODE_OK)
		{
			GST_ERROR("delete_contained_entities error %d", retcode);
			return 1;
		}

		retcode = DDS_DomainParticipantFactory_delete_participant(DDS_TheParticipantFactory, participant);
		if (retcode != DDS_RETCODE_OK)
		{
			GST_ERROR("delete_participant error %d", retcode);
			return 1;
		}
	}

	return 0;
}

static gboolean plugin_init(GstPlugin* plugin)
{
	/* Remember to set the rank if it's an element that is meant
	   to be autoplugged by decodebin. */
	return gst_element_register(plugin, "connextsink", GST_RANK_NONE, GST_TYPE_CONNEXT_SINK);
}

/* Plugin Information */
#ifndef VERSION
#define VERSION "0.0.3"
#endif
#ifndef PACKAGE
#define PACKAGE "gst_connext_package"
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME "gst-connext"
#endif
#ifndef GST_PACKAGE_ORIGIN
#define GST_PACKAGE_ORIGIN "rti.com"
#endif

GST_PLUGIN_DEFINE(GST_VERSION_MAJOR,
                  GST_VERSION_MINOR,
                  connextsink,
                  "Connext sink plugin",
                  plugin_init,
                  VERSION,
                  "Proprietary",
                  PACKAGE_NAME,
                  GST_PACKAGE_ORIGIN)
