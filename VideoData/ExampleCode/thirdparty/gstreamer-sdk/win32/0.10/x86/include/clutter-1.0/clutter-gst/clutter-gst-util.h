/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-util.h - Miscellaneous functions.
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
#error "Only <clutter-gst/clutter-gst.h> can be include directly."
#endif

#ifndef __CLUTTER_GST_UTIL_H__
#define __CLUTTER_GST_UTIL_H__

#include <clutter/clutter.h>
#include <gst/gst.h>

G_BEGIN_DECLS

ClutterInitError clutter_gst_init           (int     *argc,
                                             char  ***argv);
ClutterInitError clutter_gst_init_with_args (int            *argc,
                                             char         ***argv,
                                             const char     *parameter_string,
                                             GOptionEntry   *entries,
                                             const char     *translation_domain,
                                             GError        **error);
GstElement *     clutter_gst_video_sink_new (ClutterTexture *texture) G_GNUC_DEPRECATED;


G_END_DECLS

#endif /* __CLUTTER_GST_UTIL_H__ */
