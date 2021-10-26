#include "TileFeature.h"

TileFeature::TileFeature(const ID id)
	:
	id{ id },
	borderSprite{ getData().borderAnimatedSpriteID },
	flavorSprite{ getData().flavorAnimatedSpriteID }
{}