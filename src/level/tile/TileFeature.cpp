#include "TileFeature.h"

TileFeature::TileFeature(const ID id)
	:
	id{ id },
	sprite{ getData().animatedSpriteID }
{}