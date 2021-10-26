#include "Tile.h"

#include "../../util/Random.h"

void Tile::update(const double time)
{
	// update base sprites
	if (base.borderSprite.isAnimated())
		base.borderSprite.update(time, base.getData().isGlobalAnimation);
	if (base.flavorSprite.isAnimated())
		base.flavorSprite.update(time, base.getData().isGlobalAnimation);
	
	// update feature sprites
	if (feature.borderSprite.isAnimated())
		feature.borderSprite.update(time, feature.getData().isGlobalAnimation);
	if (feature.flavorSprite.isAnimated())
		feature.flavorSprite.update(time, feature.getData().isGlobalAnimation);
}

void Tile::setBase(const TileBase::ID id)
{
	base.id = id;
	base.borderSprite.setID(base.getData().borderAnimatedSpriteID);
	base.flavorSprite.setID(base.getData().flavorAnimatedSpriteID);
}

void Tile::setFeature(const TileFeature::ID id)
{
	feature.id = id;
	feature.borderSprite.setID(feature.getData().borderAnimatedSpriteID);
	feature.flavorSprite.setID(feature.getData().flavorAnimatedSpriteID);
}
