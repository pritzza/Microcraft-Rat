#include "TileBase.h"

TileBase::TileBase(const ID id)
	:
	id{ id },
	sprite{ getData().animatedSpriteID }
{}
