/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): mar-2001 nzc
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file DNA_group_types.h
 *  \ingroup DNA
 *
 * \brief Object groups, one object can be in many groups at once.
 */

#ifndef __DNA_GROUP_TYPES_H__
#define __DNA_GROUP_TYPES_H__

#include "DNA_defs.h"
#include "DNA_listBase.h"
#include "DNA_ID.h"

struct Object;
struct Collection;

typedef struct CollectionObject {
	struct CollectionObject *next, *prev;
	struct Object *ob;
} CollectionObject;


typedef struct CollectionChild {
	struct CollectionChild *next, *prev;
	struct Collection *collection;
} CollectionChild;


typedef struct Collection {
	ID id;

	ListBase gobject;   /* CollectionObject */
	ListBase children;  /* CollectionChild */

	struct PreviewImage *preview;

	unsigned int layer DNA_DEPRECATED;
	float dupli_ofs[3];

	short flag, pad[3];

	/* Runtime. Cache of objects in this collection and all its
	 * children. This is created on demand when e.g. some physics
	 * simulation needs it, we don't want to have it for every
	 * collections due to memory usage reasons. */
	ListBase object_cache;

	/* Runtime. List of collections that are a parent of this
	 * datablock. */
	ListBase parents;

	/* Deprecated */
	struct SceneCollection *collection DNA_DEPRECATED;
	struct ViewLayer *view_layer DNA_DEPRECATED;
} Collection;

/* Collection->flag */
enum {
	COLLECTION_RESTRICT_VIEW       = (1 << 0), /* Hidden in viewport. */
	COLLECTION_RESTRICT_SELECT     = (1 << 1), /* Not selectable in viewport. */
	COLLECTION_DISABLED_DEPRECATED = (1 << 2), /* Not used anymore */
	COLLECTION_RESTRICT_RENDER     = (1 << 3), /* Hidden in renders. */
	COLLECTION_HAS_OBJECT_CACHE    = (1 << 4), /* Runtime: object_cache is populated. */
	COLLECTION_IS_MASTER           = (1 << 5), /* Is master collection embedded in the scene. */
};

#endif  /* __DNA_GROUP_TYPES_H__ */
