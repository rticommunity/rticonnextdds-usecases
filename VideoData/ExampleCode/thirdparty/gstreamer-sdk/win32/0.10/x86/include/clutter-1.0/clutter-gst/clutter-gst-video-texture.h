/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-video-texture.h - ClutterTexture using GStreamer to display a
 *                               video stream.
 *
 * Authored By Matthew Allum  <mallum@openedhand.com>
 *
 * Copyright (C) 2006 OpenedHand
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

#ifndef __CLUTTER_GST_VIDEO_TEXTURE_H__
#define __CLUTTER_GST_VIDEO_TEXTURE_H__

#include <glib-object.h>
#include <clutter/clutter.h>
#include <gst/gstelement.h>

#include <clutter-gst/clutter-gst-types.h>

G_BEGIN_DECLS

#define CLUTTER_GST_TYPE_VIDEO_TEXTURE clutter_gst_video_texture_get_type()

#define CLUTTER_GST_VIDEO_TEXTURE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  CLUTTER_GST_TYPE_VIDEO_TEXTURE, ClutterGstVideoTexture))

#define CLUTTER_GST_VIDEO_TEXTURE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  CLUTTER_GST_TYPE_VIDEO_TEXTURE, ClutterGstVideoTextureClass))

#define CLUTTER_GST_IS_VIDEO_TEXTURE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  CLUTTER_GST_TYPE_VIDEO_TEXTURE))

#define CLUTTER_GST_IS_VIDEO_TEXTURE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  CLUTTER_GST_TYPE_VIDEO_TEXTURE))

#define CLUTTER_GST_VIDEO_TEXTURE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  CLUTTER_GST_TYPE_VIDEO_TEXTURE, ClutterGstVideoTextureClass))

typedef struct _ClutterGstVideoTexture        ClutterGstVideoTexture;
typedef struct _ClutterGstVideoTextureClass   ClutterGstVideoTextureClass;
typedef struct _ClutterGstVideoTexturePrivate ClutterGstVideoTexturePrivate;

/**
 * ClutterGstVideoTexture:
 *
 * Subclass of #ClutterTexture that displays videos using GStreamer.
 *
 * The #ClutterGstVideoTexture structure contains only private data and
 * should not be accessed directly.
 */
struct _ClutterGstVideoTexture
{
  /*< private >*/
  ClutterTexture              parent;
  ClutterGstVideoTexturePrivate *priv;
};

/**
 * ClutterGstVideoTextureClass:
 *
 * Base class for #ClutterGstVideoTexture.
 */
struct _ClutterGstVideoTextureClass
{
  /*< private >*/
  ClutterTextureClass parent_class;

  /* Future padding */
  void (* _clutter_reserved1) (void);
  void (* _clutter_reserved2) (void);
  void (* _clutter_reserved3) (void);
  void (* _clutter_reserved4) (void);
  void (* _clutter_reserved5) (void);
  void (* _clutter_reserved6) (void);
};

GType			  clutter_gst_video_texture_get_type            (void) G_GNUC_CONST;
ClutterActor *		  clutter_gst_video_texture_new                 (void);

GstElement *		  clutter_gst_video_texture_get_pipeline        (ClutterGstVideoTexture *texture);

CoglHandle		  clutter_gst_video_texture_get_idle_material   (ClutterGstVideoTexture *texture);
void			  clutter_gst_video_texture_set_idle_material   (ClutterGstVideoTexture *texture,
									 CoglHandle              material);
gchar *			  clutter_gst_video_texture_get_user_agent      (ClutterGstVideoTexture *texture);
void			  clutter_gst_video_texture_set_user_agent      (ClutterGstVideoTexture *texture,
									 const gchar *           user_agent);
ClutterGstSeekFlags	  clutter_gst_video_texture_get_seek_flags      (ClutterGstVideoTexture *texture);
void			  clutter_gst_video_texture_set_seek_flags      (ClutterGstVideoTexture *texture,
									 ClutterGstSeekFlags     flags);
ClutterGstBufferingMode	  clutter_gst_video_texture_get_buffering_mode	(ClutterGstVideoTexture *texture);
void			  clutter_gst_video_texture_set_buffering_mode	(ClutterGstVideoTexture *texture,
									 ClutterGstBufferingMode mode);
GList *                   clutter_gst_video_texture_get_audio_streams   (ClutterGstVideoTexture *texture);
gint                      clutter_gst_video_texture_get_audio_stream    (ClutterGstVideoTexture *texture);
void                      clutter_gst_video_texture_set_audio_stream    (ClutterGstVideoTexture *texture,
                                                                         gint                    index_);
GList *                   clutter_gst_video_texture_get_subtitle_tracks (ClutterGstVideoTexture *texture);
gint                      clutter_gst_video_texture_get_subtitle_track  (ClutterGstVideoTexture *texture);
void                      clutter_gst_video_texture_set_subtitle_track  (ClutterGstVideoTexture *texture,
                                                                         gint                    index_);

G_END_DECLS

#endif /* __CLUTTER_GST_VIDEO_TEXTURE_H__ */
