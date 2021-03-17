#include "src/game/envfx_snow.h"

const GeoLayout spike_ball_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_BILLBOARD_WITH_PARAMS(LAYER_ALPHA, 0, 0, 0),
		GEO_OPEN_NODE(),
			GEO_SHADOW(1, 150, 100),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, spike_ball_Spike_Ball_mesh),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, spike_ball_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
