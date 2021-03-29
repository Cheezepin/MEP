#include "src/game/envfx_snow.h"

const GeoLayout spike_ball_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 44, 0, spike_ball_ball_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_SHADOW(1, 150, 70),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, spike_ball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
