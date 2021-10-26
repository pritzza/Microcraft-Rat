#include "TileBase.h"

TileBase::TileBase(const ID id)
	:
	id{ id },
	borderSprite{ getData().borderAnimatedSpriteID },
	flavorSprite{ getData().flavorAnimatedSpriteID }
{}
