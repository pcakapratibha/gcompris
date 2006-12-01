/* gcompris - gc-sound-object.h
 *
 * Copyright (C) 2006 Yves Combe
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __GC_SOUND_OBJECT_H__
#define __GC_SOUND_OBJECT_H__

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _GCSoundObject	GCSoundObject;
typedef struct _GCSoundObjectClass	GCSoundObjectClass;

#define GC_TYPE_SOUND_OBJECT         (gc_sound_object_get_type())
#define GC_SOUND_OBJECT(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), GC_TYPE_SOUND_OBJECT, GCSoundObject))
#define GC_SOUND_OBJECT_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), GC_TYPE_SOUND_OBJECT, GCSoundObjectClass))
#define GC_IS_SOUND_OBJECT(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), GC_TYPE_SOUND_OBJECT))
#define GC_IS_SOUND_OBJECT_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), GC_TYPE_SOUND_OBJECT))
#define GC_SOUND_OBJECT_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), GC_TYPE_SOUND_OBJECT, GCSoundObjectClass))

GType gc_sound_object_get_type(void);

/* flags are stolen code from GtkObject */
typedef enum
{
  GC_SOUND_IN_DESTRUCTION	= 1 << 0, /* Used internally during dispose */
} GCSoundObjectFlags;

#define GC_SOUND_OBJECT_FLAGS(obj)		  (GC_SOUND_OBJECT (obj)->flags)
/* Macros for setting and clearing bits in the object_flags field of GtkObject.
 */
#define GC_SOUND_OBJECT_SET_FLAGS(obj,flag)	  G_STMT_START{ (GC_SOUND_OBJECT_FLAGS (obj) |= (flag)); }G_STMT_END
#define GC_SOUND_OBJECT_UNSET_FLAGS(obj,flag)  G_STMT_START{ (GC_SOUND_OBJECT_FLAGS (obj) &= ~(flag)); }G_STMT_END

struct _GCSoundObject {
  GInitiallyUnowned __parent__;

  guint32 flags;
};

struct _GCSoundObjectClass {
  GInitiallyUnownedClass base_class;

  void (*destroy)  (GCSoundObject *object);
};

G_END_DECLS


#endif
