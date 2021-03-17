#include "src/game/envfx_snow.h"

const GeoLayout blooper_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 77, 0, NULL),
		GEO_OPEN_NODE(),
			GEO_SHADOW(1, 200, 175),
			GEO_CULLING_RADIUS(1064),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -6, 0, blooper_body_mesh),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, blooper_tent1L_skinned),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 70, 2, 0, 0, 0, -151),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, blooper_tent1L_mesh),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, blooper_tent2L_skinned),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 44, 0, 0, 0, -31),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, blooper_tent2L_mesh),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, blooper_tent1R_skinned),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -70, 2, 0, 151, -90, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, blooper_tent1R_mesh),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, blooper_tent2R_skinned),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 44, 0, 31, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, blooper_tent2R_mesh),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, blooper_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
