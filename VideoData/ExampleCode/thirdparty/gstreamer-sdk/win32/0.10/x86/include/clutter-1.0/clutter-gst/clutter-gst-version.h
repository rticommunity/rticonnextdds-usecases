/*
 * Clutter-GStreamer.
 *
 * GStreamer integration library for Clutter.
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

/**
 * SECTION:clutter-gst-version
 * @short_description: Versioning Macros
 *
 * Version checking macros.
 */

#ifndef __CLUTTER_GST_VERSION_H__
#define __CLUTTER_GST_VERSION_H__

/**
 * CLUTTER_GST_MAJOR_VERSION:
 *
 * ClutterGst major version (e.g. "1", if %CLUTTER_GST_VERSION is "1.2.3")
 */
#define CLUTTER_GST_MAJOR_VERSION   (1)

/**
 * CLUTTER_GST_MINOR_VERSION:
 *
 * ClutterGst minor version (e.g. "2", if %CLUTTER_GST_VERSION is "1.2.3")
 */
#define CLUTTER_GST_MINOR_VERSION   (6)

/**
 * CLUTTER_GST_MICRO_VERSION:
 *
 * ClutterGst micro version (e.g. "3", if %CLUTTER_GST_VERSION is "1.2.3")
 */
#define CLUTTER_GST_MICRO_VERSION   (0)

/**
 * CLUTTER_GST_VERSION:
 *
 * ClutterGst full version (e.g. "1.2.3")
 */
#define CLUTTER_GST_VERSION         (1.6.0)

/**
 * CLUTTER_GST_VERSION_S:
 *
 * ClutterGst full version, encoded as a string.
 */
#define CLUTTER_GST_VERSION_S       "1.6.0"

/**
 * CLUTTER_GST_VERSION_HEX:
 *
 * ClutterGst full version, encoded as an hexadecimal value.
 */
#define CLUTTER_GST_VERSION_HEX     ((CLUTTER_GST_MAJOR_VERSION << 24) | \
                                     (CLUTTER_GST_MINOR_VERSION << 16) | \
                                     (CLUTTER_GST_MICRO_VERSION << 8))

/**
 * CLUTTER_GST_CHECK_VERSION:
 * @major: major version, like 1 in 1.2.3
 * @minor: minor version, like 2 in 1.2.3
 * @micro: micro version, like 3 in 1.2.3
 *
 * Evaluates to %TRUE if the version of ClutterGst is greater than
 * the @major, @minor and @micro values.
 */
#define CLUTTER_GST_CHECK_VERSION(major,minor,micro) \
        (CLUTTER_GST_MAJOR_VERSION > (major) || \
         (CLUTTER_GST_MAJOR_VERSION == (major) && CLUTTER_GST_MINOR_VERSION > (minor)) || \
         (CLUTTER_GST_MAJOR_VERSION == (major) && CLUTTER_GST_MINOR_VERSION == (minor) && CLUTTER_GST_MICRO_VERSION >= (micro)))

#endif /* __CLUTTER_GST_VERSION_H__ */
