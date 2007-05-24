
/* Generated data (by glib-mkenums) */

#include <ccc/cc-enumerations.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif

#include <glib/gi18n.h>
/* enumerations from "cc-item.h" */
#include "cc-item.h"
GType
cc_item_flags_get_type(void) {
	static GType etype = 0;
	if(!etype) {
		static const GFlagsValue values[] = {
			{CC_CAN_FOCUS, "CC_CAN_FOCUS", N_("can-focus")},
			{CC_DISPOSED, "CC_DISPOSED", N_("disposed")},
			{CC_GRID_ALIGNED, "CC_GRID_ALIGNED", N_("grid-aligned")},
			{0, NULL, NULL}
		};

		etype = g_flags_register_static("CcItemFlags", values);
	}

	return etype;
}
/* enumerations from "cc-utils.h" */
#include "cc-utils.h"
GType
cc_zoom_mode_get_type(void) {
	static GType etype = 0;
	if(!etype) {
		static const GEnumValue values[] = {
			{CC_ZOOM_PIXELS, "CC_ZOOM_PIXELS", N_("pixels")},
			{CC_ZOOM_WIDTH, "CC_ZOOM_WIDTH", N_("width")},
			{CC_ZOOM_HEIGHT, "CC_ZOOM_HEIGHT", N_("height")},
			{CC_ZOOM_AUTO, "CC_ZOOM_AUTO", N_("auto")},
			{0, NULL, NULL}
		};

		etype = g_enum_register_static("CcZoomMode", values);
	}

	return etype;
}

/* Generated data ends here */

