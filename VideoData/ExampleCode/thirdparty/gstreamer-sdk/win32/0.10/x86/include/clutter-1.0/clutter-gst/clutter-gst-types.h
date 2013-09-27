/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
 *
 * clutter-gst-types.h - Clutter-Gst common types
 *
 * Authored By Lionel Landwerlin <lionel.g.landwerlin@linux.intel.com>
 *
 * Copyright (C) 2011 Intel Corporation
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

#ifndef __CLUTTER_GST_TYPES_H__
#define __CLUTTER_GST_TYPES_H__

/**
 * ClutterGstSeekFlags:
 * @CLUTTER_GST_SEEK_FLAG_NONE: Fast seeks (key frame boundaries, default)
 * @CLUTTER_GST_SEEK_FLAG_ACCURATE: Accurate seeks (potentially slower)
 *
 * Flags that can be given to clutter_gst_video_texture_set_seek_flags().
 *
 * Since: 1.4
 */
typedef enum _ClutterGstSeekFlags
{
  CLUTTER_GST_SEEK_FLAG_NONE     = 0,
  CLUTTER_GST_SEEK_FLAG_ACCURATE = 1 << 0
} ClutterGstSeekFlags;

/**
 * ClutterGstBufferingMode:
 * @CLUTTER_GST_BUFFERING_MODE_STREAM: In-memory buffering
 * @CLUTTER_GST_BUFFERING_MODE_DOWNLOAD: On-disk buffering
 *
 * Different buffering policies clutter-gst supports
 *
 * Since: 1.4
 */
typedef enum _ClutterGstBufferingMode
{
  CLUTTER_GST_BUFFERING_MODE_STREAM,
  CLUTTER_GST_BUFFERING_MODE_DOWNLOAD
} ClutterGstBufferingMode;

#endif /* __CLUTTER_GST_TYPES_H__ */
