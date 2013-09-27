/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-video-sink.h - Gstreamer Video Sink that renders to a
 *                            Clutter Texture.
 *
 * Authored by Jonathan Matthew  <jonathan@kaolin.wh9.net>
 *
 * Copyright (C) 2007 OpenedHand
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#if !defined(__CLUTTER_GST_H_INSIDE__) && !defined(CLUTTER_GST_COMPILATION)
#error "Only <clutter-gst/clutter-gst.h> can be included directly."
#endif

#ifndef __CLUTTER_GST_VIDEO_SINK_H__
#define __CLUTTER_GST_VIDEO_SINK_H__

#include <glib-object.h>
#include <gst/base/gstbasesink.h>
#include <clutter/clutter.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_VIDEO_SINK clutter_gst_video_sink_get_type()

#define CLUTTER_GST_VIDEO_SINK(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CLUTTER_GST_TYPE_VIDEO_SINK, ClutterGstVideoSink))

#define CLUTTER_GST_VIDEO_SINK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CLUTTER_GST_TYPE_VIDEO_SINK, ClutterGstVideoSinkClass))

#define CLUTTER_GST_IS_VIDEO_SINK(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CLUTTER_GST_TYPE_VIDEO_SINK))

#define CLUTTER_GST_IS_VIDEO_SINK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CLUTTER_GST_TYPE_VIDEO_SINK))

#define CLUTTER_GST_VIDEO_SINK_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CLUTTER_GST_TYPE_VIDEO_SINK, ClutterGstVideoSinkClass))

typedef struct _ClutterGstVideoSink        ClutterGstVideoSink;
typedef struct _ClutterGstVideoSinkClass   ClutterGstVideoSinkClass;
typedef struct _ClutterGstVideoSinkPrivate ClutterGstVideoSinkPrivate;

/**
 * ClutterGstVideoSink:
 *
 * Class implementing a GStreamer sink element for #ClutterTexture<!-- -->s.
 *
 * The #ClutterGstVideoSink structure contains only private data and should
 * not be accessed directly.
 */
struct _ClutterGstVideoSink
{
  /*< private >*/
  GstBaseSink                 parent;
  ClutterGstVideoSinkPrivate *priv;
};

/**
 * ClutterGstVideoSinkClass:
 *
 * Base class for #ClutterGstVideoSink.
 */
struct _ClutterGstVideoSinkClass
{
  /*< private >*/
  GstBaseSinkClass parent_class;

  /* Future padding */
  void (* _clutter_reserved1) (void);
  void (* _clutter_reserved2) (void);
  void (* _clutter_reserved3) (void);
  void (* _clutter_reserved4) (void);
  void (* _clutter_reserved5) (void);
  void (* _clutter_reserved6) (void);
};

GType       clutter_gst_video_sink_get_type    (void) G_GNUC_CONST;

G_END_DECLS

#endif /* __CLUTTER_GST_VIDEO_SINK_H__ */
