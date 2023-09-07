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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>
#include <gst/base/gstpushsrc.h>
#include <gst/gst.h>
#include <gst/video/video.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "gstconnextsrc.h"

GST_DEBUG_CATEGORY_STATIC(gst_connextsrc_debug_category);
#define GST_CAT_DEFAULT gst_connextsrc_debug_category
#define PROFILE_NAME_MAX_LEN 200

/* prototypes */

/* set gstreamer property */
static void gst_connextsrc_set_property(GObject* object, guint property_id, const GValue* value, GParamSpec* pspec);

/* get gstreamer property */
static void gst_connextsrc_get_property(GObject* object, guint property_id, GValue* value, GParamSpec* pspec);

/* dispose connextsrc */
static void gst_connextsrc_dispose(GObject* object);

/* finalize connextsrc */
static void gst_connextsrc_finalize(GObject* object);

/* start connextsrc plugin */
static gboolean gst_connextsrc_start(GstBaseSrc* src);

/* stop connextsrc plugin */
static gboolean gst_connextsrc_stop(GstBaseSrc* src);

/* subscribe to get frame */
static GstFlowReturn gst_connextsrc_create(GstPushSrc* src, GstBuffer** buf);

/* handle caps events */
static gboolean gst_connextsrc_src_event(GstPad* pad, GstObject* parent, GstEvent* event);

/* parse qos profiles */
static int gst_connextsrc_get_qos_library_profile(GstConnextSrc* connext_sink, gchar* qosProfile, char* qos_library_name, char* qos_profile_name);

/* initialize subscriber */
static int gst_connextsrc_subscriber_init(GstConnextSrc* connextsrc);

/* shutdown subscriber */
static int gst_connextsrc_subscriber_shutdown(DDS_DomainParticipant* participant);

/* create content filter */
static void gst_connextsrc_create_connext_reader_content_filter(GstConnextSrc* connextsrc);

/* update content filter */
static int gst_connextsrc_update_connext_reader_content_filter(GstConnextSrc* connextsrc);

/* element methods */
static GstStateChangeReturn gst_connextsrc_change_state(GstElement* element, GstStateChange transition);

#define DEFAULT_QOS "BuiltinQosLibExp::Generic.StrictReliable"

enum
{
	PROP_0,
	PROP_CONNEXT_DOMAIN_ID,
	PROP_CONNEXT_TOPIC,
	PROP_CONNEXT_KEY,
	PROP_CONNEXT_DP_QOS_PROFILE,
	PROP_CONNEXT_DR_QOS_PROFILE,
	PROP_EXTERNAL_CONNEXT_PARTICIPANT
};

#define CONNEXTSRC_VIDEO_CAPS                               \
	"video/x-h264, stream-format=(string)byte-stream, " \
	"alignment=(string) au, width=(int)1920, height=(int)1080, framerate=(fraction)30/1"

#define CONNEXTSRC_VIDEO_CAPS2               \
	"video/x-raw, format=(string) RGB, " \
	"width = (int) 1920, "               \
	"height = (int) 1080, "              \
	"framerate = (fraction) 30/1"

/* pad templates */
static GstStaticPadTemplate gst_connextsrc_src_template = GST_STATIC_PAD_TEMPLATE("src",
                                                                              GST_PAD_SRC,
                                                                              GST_PAD_ALWAYS,
                                                                              GST_STATIC_CAPS(CONNEXTSRC_VIDEO_CAPS));

/* class initialization */

G_DEFINE_TYPE_WITH_CODE(
    GstConnextSrc,
    gst_connextsrc,
    GST_TYPE_PUSH_SRC,
    GST_DEBUG_CATEGORY_INIT(gst_connextsrc_debug_category, "connextsrc", 0, "debug category for connextsrc element"))

static void gst_connextsrc_class_init(GstConnextSrcClass* class)
{
	GObjectClass* gobject_class = G_OBJECT_CLASS(class);
	GstElementClass* element_class = GST_ELEMENT_CLASS(class);
	GstBaseSrcClass* base_src_class = GST_BASE_SRC_CLASS(class);
	GstPushSrcClass* push_src_class = GST_PUSH_SRC_CLASS(class);

	/* Setting up pads and setting metadata should be moved to
	   base_class_init if you intend to subclass this class. */
	gst_element_class_add_pad_template(GST_ELEMENT_CLASS(class), gst_static_pad_template_get(&gst_connextsrc_src_template));

	gst_element_class_set_static_metadata(GST_ELEMENT_CLASS(class),
	                                      "Connext VideoStream Source",
	                                      "Source/Network",
	                                      "Receive data over networks using Connext middleware",
	                                      "RTI <community@rti.com>");

	gobject_class->set_property = gst_connextsrc_set_property;
	gobject_class->get_property = gst_connextsrc_get_property;
	gobject_class->dispose = gst_connextsrc_dispose;
	gobject_class->finalize = gst_connextsrc_finalize;
	base_src_class->start = GST_DEBUG_FUNCPTR(gst_connextsrc_start);
	base_src_class->stop = GST_DEBUG_FUNCPTR(gst_connextsrc_stop);
	push_src_class->create = GST_DEBUG_FUNCPTR(gst_connextsrc_create);

	element_class->change_state = gst_connextsrc_change_state;

	/* define properties */
	g_object_class_install_property(
			gobject_class,
			PROP_CONNEXT_DOMAIN_ID,
			g_param_spec_uint(
					"domain",
					"Connext domain ID",
					"The Domain ID used for the Connext publisher",
					0,
					10000,
					0,
					G_PARAM_READWRITE));

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
					"Default QoS profile used when creating the the DP of this sink element",
					DEFAULT_QOS,
					G_PARAM_READWRITE));

	g_object_class_install_property(
			gobject_class,
			PROP_CONNEXT_DR_QOS_PROFILE,
			g_param_spec_string(
					"dr-qos-profile",
					"Connext DR Qos Profile",
					"Default QoS profile used when creating the the DR of this sink element",
					DEFAULT_QOS,
					G_PARAM_READWRITE));

	g_object_class_install_property(
			gobject_class,
	        PROP_EXTERNAL_CONNEXT_PARTICIPANT,
	        g_param_spec_pointer(
					"participant",
	                "External Connext Participant entity",
	                "Pointer to an externally created Connext participant entity",
	                G_PARAM_WRITABLE | G_PARAM_READABLE));
}

void sequencesListener_on_requested_deadline_missed(__attribute__((unused)) void* listener_data,
                                                    __attribute__((unused)) DDS_DataReader* reader,
                                                    __attribute__((unused))
                                                    const struct DDS_RequestedDeadlineMissedStatus* status)
{
}

void sequencesListener_on_requested_incompatible_qos(__attribute__((unused)) void* listener_data,
                                                     __attribute__((unused)) DDS_DataReader* reader,
                                                     __attribute__((unused))
                                                     const struct DDS_RequestedIncompatibleQosStatus* status)
{
}

void sequencesListener_on_sample_rejected(__attribute__((unused)) void* listener_data,
                                          __attribute__((unused)) DDS_DataReader* reader,
                                          __attribute__((unused)) const struct DDS_SampleRejectedStatus* status)
{
}

void sequencesListener_on_liveliness_changed(__attribute__((unused)) void* listener_data,
                                             __attribute__((unused)) DDS_DataReader* reader,
                                             __attribute__((unused)) const struct DDS_LivelinessChangedStatus* status)
{
}

void sequencesListener_on_sample_lost(__attribute__((unused)) void* listener_data,
                                      __attribute__((unused)) DDS_DataReader* reader,
                                      __attribute__((unused)) const struct DDS_SampleLostStatus* status)
{
}

void sequencesListener_on_subscription_matched(__attribute__((unused)) void* listener_data,
                                               __attribute__((unused)) DDS_DataReader* reader,
                                               __attribute__((unused))
                                               const struct DDS_SubscriptionMatchedStatus* status)
{
}

void sequencesListener_on_data_available(__attribute__((unused)) void* listener_data, DDS_DataReader* reader)
{
	Video_StreamDataReader* video_reader = Video_StreamDataReader_narrow(reader);
	GstConnextSrc* connextsrc = (GstConnextSrc*)listener_data;
	if (video_reader == NULL)
	{
		GST_ERROR_OBJECT(connextsrc, "CONNEXTSRC:on_data_available: Error receiving data\n");
		return;
	}

	struct Video_StreamSeq dataSeq;
	Video_StreamSeq_initialize(&dataSeq);
	struct DDS_SampleInfoSeq infoSeq;
	DDS_SampleInfoSeq_initialize(&infoSeq);
	DDS_ReturnCode_t retCode = DDS_RETCODE_OK;

	/* take samples */
	retCode = Video_StreamDataReader_take(
			video_reader,
			&dataSeq,
			&infoSeq,
			DDS_LENGTH_UNLIMITED,
			DDS_ANY_SAMPLE_STATE,
			DDS_ANY_VIEW_STATE,
			DDS_ANY_INSTANCE_STATE);

	if (retCode != DDS_RETCODE_OK)
	{
		GST_ERROR_OBJECT(connextsrc, "on_data_available: failed to take new samples.");
	}

	/* process samples */
	for (int i = 0; i < Video_StreamSeq_get_length(&dataSeq); i++)
	{
		if (DDS_SampleInfoSeq_get_reference(&infoSeq, i)->valid_data)
		{

			Video_Stream* sample = Video_StreamSeq_get_reference(&dataSeq, i);
			uint32_t frame_buffer_size = DDS_OctetSeq_get_length(&sample->frame);
			DDS_Octet* data = DDS_OctetSeq_get_contiguous_buffer(&sample->frame);

			if(frame_buffer_size > 0)
			{
				connextsrc->connext.frame_buffer = gst_buffer_new_allocate(NULL, frame_buffer_size, NULL);
				
				if (connextsrc->connext.frame_buffer != NULL)
				{
					/* copy the frame to a gstreamer buffer and push it into the queue*/
					gst_buffer_fill(connextsrc->connext.frame_buffer, 0, data, frame_buffer_size);
					g_async_queue_push(connextsrc->g_filled_frame_queue, connextsrc->connext.frame_buffer);
				}
			}
		}
	}

	retCode = Video_StreamDataReader_return_loan(video_reader, &dataSeq, &infoSeq);
	if (retCode != DDS_RETCODE_OK)
	{
		GST_ERROR_OBJECT(connextsrc,"on_data_available: Failed to return loaned samples");
	}
}

static void gst_connextsrc_init(GstConnextSrc* connextsrc)
{
	connextsrc->connext.domainId = 0;
	connextsrc->connext.topicName = NULL;
	connextsrc->connext.participant = NULL;
	connextsrc->connext.key = g_strdup("*"); 
	connextsrc->connext.prevKey = g_strdup("*");
	connextsrc->connext.dpQosProfile = g_strdup(DEFAULT_QOS);
	connextsrc->connext.drQosProfile = g_strdup(DEFAULT_QOS);

	gst_base_src_set_live(GST_BASE_SRC(connextsrc), TRUE);

	gst_pad_set_event_function(GST_BASE_SRC(connextsrc)->srcpad, gst_connextsrc_src_event);

	GST_INFO_OBJECT(connextsrc, "connextsrc initialization complete.");
}

/* start and stop processing, ideal for opening/closing the resource */
static gboolean gst_connextsrc_start(GstBaseSrc* src)
{
	GstConnextSrc* connextsrc = GST_CONNEXTSRC(src);

	GST_TRACE_OBJECT(connextsrc, "start");

	/* Prepare queue for filled frames from which connextsrc_create can take them */
	connextsrc->g_filled_frame_queue = g_async_queue_new();

	if(connextsrc->g_filled_frame_queue != NULL) 
	{
		return TRUE;
	}
	else
	{
		GST_ERROR("Error initializing frame queue");
		return FALSE;
	}
}

static gboolean gst_connextsrc_stop(GstBaseSrc* src)
{
	GstConnextSrc* connextsrc = GST_CONNEXTSRC(src);

	GST_TRACE_OBJECT(connextsrc, "Stopping ConnextSrc");

	/* Unref the filled frame queue so it is deleted properly */
	g_async_queue_unref(connextsrc->g_filled_frame_queue);
	connextsrc->g_filled_frame_queue = NULL;

	return TRUE;
}

void gst_connextsrc_set_property(GObject* object, guint property_id, const GValue* value, GParamSpec* pspec)
{
	GstConnextSrc* connextsrc = GST_CONNEXTSRC(object);

	GST_DEBUG_OBJECT(connextsrc, "set_property");

	switch (property_id)
	{
		case PROP_CONNEXT_DOMAIN_ID: connextsrc->connext.domainId = g_value_get_uint(value); break;
		case PROP_CONNEXT_TOPIC:
		{
			g_free(connextsrc->connext.topicName);
			connextsrc->connext.topicName = g_value_dup_string(value);
			break;
		}
		case PROP_CONNEXT_KEY:
		{
			g_free(connextsrc->connext.prevKey);
			connextsrc->connext.prevKey = connextsrc->connext.key;
			connextsrc->connext.key = g_value_dup_string(value);
			break;
		}
		case PROP_CONNEXT_DP_QOS_PROFILE:
		{
			g_free(connextsrc->connext.dpQosProfile);
			connextsrc->connext.dpQosProfile = g_value_dup_string(value);
			break;
		}
		case PROP_CONNEXT_DR_QOS_PROFILE:
		{
			g_free(connextsrc->connext.drQosProfile);
			connextsrc->connext.drQosProfile = g_value_dup_string(value);
			break;
		}
		case PROP_EXTERNAL_CONNEXT_PARTICIPANT:
		{
			g_free(connextsrc->connext.participant);
			connextsrc->connext.participant = (DDS_DomainParticipant*)(g_value_get_pointer(value));
			GST_INFO_OBJECT(connextsrc,"Connext Participant pointer set from external source; participant pointer is: %p\n",
			       (void*)connextsrc->connext.participant);
			break;
		}
		default: G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec); break;
	}
}

void gst_connextsrc_get_property(GObject* object, guint property_id, GValue* value, GParamSpec* pspec)
{
	GstConnextSrc* connextsrc = GST_CONNEXTSRC(object);

	GST_DEBUG_OBJECT(connextsrc, "get_property");

	switch (property_id)
	{
		case PROP_CONNEXT_DOMAIN_ID: g_value_set_uint(value, connextsrc->connext.domainId); break;
		case PROP_CONNEXT_TOPIC: g_value_set_string(value, connextsrc->connext.topicName); break;
		case PROP_CONNEXT_KEY: g_value_set_string(value, connextsrc->connext.key); break;
		case PROP_CONNEXT_DP_QOS_PROFILE: g_value_set_string(value, connextsrc->connext.dpQosProfile); break;
		case PROP_CONNEXT_DR_QOS_PROFILE: g_value_set_string(value, connextsrc->connext.drQosProfile); break;
		case PROP_EXTERNAL_CONNEXT_PARTICIPANT: g_value_set_pointer(value, connextsrc->connext.participant); break;
		default: G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec); break;
	}
}

void gst_connextsrc_dispose(GObject* object)
{
	GstConnextSrc* connextsrc = GST_CONNEXTSRC(object);
	GST_DEBUG_OBJECT(connextsrc, "dispose");

	/* clean up as possible.  may be called multiple times */
	if (gst_connextsrc_subscriber_shutdown(connextsrc->connext.participant))
	{
		GST_ERROR("Failed to shutdown Connext subscriber cleanly!");
	}

	G_OBJECT_CLASS(gst_connextsrc_parent_class)->dispose(object);
}

void gst_connextsrc_finalize(GObject* object)
{
	GstConnextSrc* connextsrc = GST_CONNEXTSRC(object);

	GST_DEBUG_OBJECT(connextsrc, "finalize");

	/* clean up object here */

	G_OBJECT_CLASS(gst_connextsrc_parent_class)->finalize(object);
}

static GstStateChangeReturn gst_connextsrc_change_state(GstElement* element, GstStateChange transition)
{
	GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
	GstConnextSrc* connextsrc = GST_CONNEXTSRC(element);
	switch (transition)
	{
		case GST_STATE_CHANGE_NULL_TO_READY:
		{
			if (connextsrc->connext.topicName == NULL)
			{
				GST_ERROR("\nCONNEXTSRC: Connext topic not specified in the pipeline. Cannot continue!\n\n");
				return GST_STATE_CHANGE_FAILURE;
			}

			char msg[300];
			snprintf(msg, sizeof(msg),
			        "CONNEXTSRC: Domain ID is %d; Topic is '%s' with key '%s', DP QoS is '%s' and DR QoS is '%s'",
			        connextsrc->connext.domainId,
			        connextsrc->connext.topicName,
			        connextsrc->connext.key,
					connextsrc->connext.dpQosProfile,
					connextsrc->connext.drQosProfile);
			printf("%s\n", msg);
			GST_INFO_OBJECT(connextsrc, "%s", msg);

			if (gst_connextsrc_subscriber_init(connextsrc))
			{
				return GST_STATE_CHANGE_FAILURE;
			}
			break;
		}
		default: break;
	}

	ret = GST_ELEMENT_CLASS(gst_connextsrc_parent_class)->change_state(element, transition);

	gst_connextsrc_update_connext_reader_content_filter(connextsrc);
	return ret;
}

static int gst_connextsrc_get_qos_library_profile(GstConnextSrc* connextsrc, gchar* qosProfile, char* qos_library_name, char* qos_profile_name)
{
	if(strlen(qosProfile) >= PROFILE_NAME_MAX_LEN){
		GST_ERROR_OBJECT(connextsrc, "QoS profile string is too long: %s", qosProfile);
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
		GST_ERROR_OBJECT(connextsrc, "Cannot parse provided QoS profile string: %s", qosProfile);
		return 1;
	}

	token = strtok(NULL, delim);
	if (token != NULL)
	{
		strcpy(qos_profile_name, token);
	}
	else
	{
		GST_ERROR_OBJECT(connextsrc, "Cannot parse provided QoS profile string: %s", qosProfile);
		return 1;
	}
	return 0;
}

static GstFlowReturn gst_connextsrc_create(GstPushSrc* src, GstBuffer** buf)
{
	GstConnextSrc* connextsrc = GST_CONNEXTSRC(src);

	bool frame_ready = false;
	GstBuffer* frame;

	/* Try to get a filled frame for 10 microseconds */
	const int wait_timeout = 10;

	do
	{
		/* Wait until we can get a filled frame from the on_data_available Connext callback */ 
		frame = NULL;
		GstState state;
		do
		{
			frame = g_async_queue_timeout_pop(connextsrc->g_filled_frame_queue, wait_timeout);

			/* Get the current state of the element. Should return immediately since we are not doing ASYNC state
			changes but wait at most for 100 nanoseconds */ 
			const int state_read_timeout = 100;
			gst_element_get_state(GST_ELEMENT(connextsrc), &state, NULL, state_read_timeout);
			if (state != GST_STATE_PLAYING)
			{
				/* The src should not create any more data. Stop waiting for frame and do not fill buf */
				GST_INFO_OBJECT(connextsrc, "Element state is no longer \"GST_STATE_PLAYING\". Aborting create call.");
				return GST_FLOW_FLUSHING;
			}
		} while (frame == NULL);

		if (frame != NULL)
		{
			GST_TRACE_OBJECT(connextsrc, "Connext frame complete");
			frame_ready = true;
		}
		else
		{
			GST_DEBUG_OBJECT(connextsrc, "Incomplete frame from Connext sequence");
			return GST_FLOW_ERROR;
		}

	} while (!frame_ready);

	GstClock* clock = NULL;
	GstClockTime base_time, timestamp = GST_CLOCK_TIME_NONE;
	/* obtain element clock and base time */
	GST_OBJECT_LOCK(src);
	if ((clock = GST_ELEMENT_CLOCK(src)) != NULL)
	{
		gst_object_ref(clock);
	}
	base_time = GST_ELEMENT_CAST(src)->base_time;
	GST_OBJECT_UNLOCK(src);

	timestamp = gst_clock_get_time(clock) - base_time;
	GST_BUFFER_DTS(frame) = timestamp;
	GST_BUFFER_PTS(frame) = GST_BUFFER_DTS(frame);

	/* Set filled GstBuffer as output to pass down the pipeline */
	*buf = frame;

	return GST_FLOW_OK;
}

static gboolean gst_connextsrc_src_event(GstPad* pad, GstObject* parent, GstEvent* event)
{
	gboolean ret;
	GstConnextSrc* src = GST_CONNEXTSRC(parent);

	switch (GST_EVENT_TYPE(event))
	{
		case GST_EVENT_CAPS:
			ret = gst_pad_push_event(GST_BASE_SRC(src)->srcpad, event);
			GST_INFO("Caps event handled!");
			break;
		default: ret = gst_pad_event_default(pad, parent, event); break;
	}
	return ret;
}

static int gst_connextsrc_subscriber_init(GstConnextSrc* connextsrc)
{
	char dpQosLib[PROFILE_NAME_MAX_LEN];
	char dpQosProfile[PROFILE_NAME_MAX_LEN];
	char drQosLib[PROFILE_NAME_MAX_LEN];
	char drQosProfile[PROFILE_NAME_MAX_LEN];

	int parse_ret = gst_connextsrc_get_qos_library_profile(connextsrc, connextsrc->connext.dpQosProfile, dpQosLib, dpQosProfile);
	if (parse_ret)
	{
		return 1;
	}
	parse_ret = gst_connextsrc_get_qos_library_profile(connextsrc, connextsrc->connext.drQosProfile, drQosLib, drQosProfile);
	if (parse_ret)
	{
		return 1;
	}

	if (connextsrc->connext.participant == NULL)
	{
		GST_INFO_OBJECT(connextsrc, "CONNEXTSRC: Creating local Connext participant entity\n");
		DDS_ReturnCode_t retcode = DDS_DomainParticipantFactory_set_default_participant_qos_with_profile(
		    DDS_TheParticipantFactory, dpQosLib, dpQosProfile);
		if (retcode != DDS_RETCODE_OK)
		{
			GST_ERROR_OBJECT(connextsrc, "error %d; cannot set partipant qos to %s::%s", retcode, dpQosLib, dpQosProfile);
			return 1;
		}

		connextsrc->connext.participant = DDS_DomainParticipantFactory_create_participant_with_profile(
		    DDS_TheParticipantFactory, connextsrc->connext.domainId, dpQosLib, dpQosProfile, NULL, DDS_STATUS_MASK_NONE);
		if (connextsrc->connext.participant == NULL)
		{
			GST_ERROR_OBJECT(connextsrc, "create_participant error");
			return 1;
		}
	}
	else
	{
		GST_INFO_OBJECT(connextsrc, "CONNEXTSRC: Using externally created Connext participant\n");
	}

	connextsrc->connext.subscriber = DDS_DomainParticipant_create_subscriber(
	    connextsrc->connext.participant, &DDS_SUBSCRIBER_QOS_DEFAULT, NULL, DDS_STATUS_MASK_NONE);
	if (connextsrc->connext.subscriber == NULL)
	{
		GST_ERROR_OBJECT(connextsrc, "create_subscriber error");
		return 1;
	}

	const char* type_name = NULL;
	type_name = Video_StreamTypeSupport_get_type_name();
	DDS_ReturnCode_t retcode = Video_StreamTypeSupport_register_type(connextsrc->connext.participant, type_name);
	if (retcode != DDS_RETCODE_OK)
	{
		GST_ERROR_OBJECT(connextsrc, "register_type error");
		return 1;
	}

	connextsrc->connext.topic = DDS_DomainParticipant_create_topic(
	    connextsrc->connext.participant, connextsrc->connext.topicName, type_name, &DDS_TOPIC_QOS_DEFAULT, NULL, DDS_STATUS_MASK_NONE);
	if (connextsrc->connext.topic == NULL)
	{
		GST_ERROR_OBJECT(connextsrc, "create_topic error");
		return 1;
	}

	connextsrc->connext.reader_listener.as_listener.listener_data = (void*)connextsrc;
	connextsrc->connext.reader_listener.on_requested_deadline_missed = sequencesListener_on_requested_deadline_missed;
	connextsrc->connext.reader_listener.on_requested_incompatible_qos = sequencesListener_on_requested_incompatible_qos;
	connextsrc->connext.reader_listener.on_sample_rejected = sequencesListener_on_sample_rejected;
	connextsrc->connext.reader_listener.on_liveliness_changed = sequencesListener_on_liveliness_changed;
	connextsrc->connext.reader_listener.on_sample_lost = sequencesListener_on_sample_lost;
	connextsrc->connext.reader_listener.on_subscription_matched = sequencesListener_on_subscription_matched;
	connextsrc->connext.reader_listener.on_data_available = sequencesListener_on_data_available;

	gst_connextsrc_create_connext_reader_content_filter(connextsrc);

	connextsrc->connext.reader = DDS_Subscriber_create_datareader_with_profile(
			connextsrc->connext.subscriber,
			DDS_ContentFilteredTopic_as_topicdescription(connextsrc->connext.cft),
			drQosLib,
			drQosProfile,
			&(connextsrc->connext.reader_listener),
			DDS_STATUS_MASK_ALL);

	if (connextsrc->connext.reader == NULL)
	{
		GST_ERROR_OBJECT(connextsrc, "create_datareader error");
		return 1;
	}

	connextsrc->connext.videoStream_reader = Video_StreamDataReader_narrow(connextsrc->connext.reader);
	if (connextsrc->connext.videoStream_reader == NULL)
	{
		GST_ERROR_OBJECT(connextsrc, "DataReader_narrow error");
		return 1;
	}
	return 0;
}

static void gst_connextsrc_create_connext_reader_content_filter(GstConnextSrc* connextsrc)
{
	const char* cft_param_list[] = {connextsrc->connext.key};
	DDS_StringSeq_initialize(&connextsrc->connext.cft_parameters);
	DDS_StringSeq_set_maximum(&connextsrc->connext.cft_parameters, 1);
	DDS_StringSeq_from_array(&connextsrc->connext.cft_parameters, cft_param_list, 1);
	connextsrc->connext.cft = DDS_DomainParticipant_create_contentfilteredtopic_with_filter(
			connextsrc->connext.participant,
	        "ContentFilteredTopic",
	        connextsrc->connext.topic,
	        "id MATCH %0",
	        &connextsrc->connext.cft_parameters,
	        DDS_STRINGMATCHFILTER_NAME);

}

static int gst_connextsrc_update_connext_reader_content_filter(GstConnextSrc* connextsrc)
{
	if (strcmp(connextsrc->connext.prevKey, connextsrc->connext.key) != 0)
	{
		printf(
		    "Changing RTI content filter; from '%s' (prev) vs '%s' (latest) \n", connextsrc->connext.prevKey, connextsrc->connext.key);
		/* set_expression_parameters */
		DDS_String_free(DDS_StringSeq_get(&connextsrc->connext.cft_parameters, 0));
		char RTI_key_format[PROFILE_NAME_MAX_LEN];
		
		if((strlen(connextsrc->connext.key) + 3) > PROFILE_NAME_MAX_LEN)
		{
			GST_ERROR_OBJECT(connextsrc, "new key is too long");
			return -1;
		}
		snprintf(RTI_key_format, sizeof(RTI_key_format), "'%s'", connextsrc->connext.key);
		*DDS_StringSeq_get_reference(&connextsrc->connext.cft_parameters, 0) = DDS_String_dup(RTI_key_format);

		printf("CONNEXTSRC: updating RTI content filter with key value: %s\n", connextsrc->connext.key);

		DDS_ReturnCode_t retcode = DDS_ContentFilteredTopic_set_expression_parameters(
				connextsrc->connext.cft,
				&connextsrc->connext.cft_parameters);
		if (retcode != DDS_RETCODE_OK)
		{
			GST_ERROR_OBJECT(connextsrc, "CONNEXTSRC: content filter set failed with error: %d\n", retcode);
			return -1;
		}

		//free the previous key and update it to match the new key
		g_free(connextsrc->connext.prevKey);
		connextsrc->connext.prevKey = g_strdup(connextsrc->connext.key);
	}
	return 0;
}

static int gst_connextsrc_subscriber_shutdown(DDS_DomainParticipant* participant)
{
	DDS_ReturnCode_t retcode;
	GST_INFO("Calling Connext subscriber shut down\n");

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

	GST_INFO("subscriber_shutdown complete");

	return 0;
}

static gboolean plugin_init(GstPlugin* plugin)
{
	/* Remember to set the rank if it's an element that is meant
	   to be autoplugged by decodebin. */
	return gst_element_register(plugin, "connextsrc", GST_RANK_NONE, GST_TYPE_CONNEXTSRC);
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
                  connextsrc,
                  "Connext source plugin",
                  plugin_init,
                  VERSION,
                  "Proprietary",
                  PACKAGE_NAME,
                  GST_PACKAGE_ORIGIN)
