#include "Tile.h"

#include "../../util/Random.h"

void Tile::update(const double time)
{
	AnimatedSprite& baseSprite{ base.sprite };
	AnimatedSprite& featureSprite{ feature.sprite };

	if (baseSprite.isAnimated())
		baseSprite.update(time, base.getData().isGlobalAnimation);
	
	if (featureSprite.isAnimated())
		featureSprite.update(time, feature.getData().isGlobalAnimation);
}

void Tile::setBase(const TileBase::ID id)
{
	base.id = id;
	base.sprite.setID(base.getData().animatedSpriteID);
}

void Tile::setFeature(const TileFeature::ID id)
{
	feature.id = id;
	feature.sprite.setID(feature.getData().animatedSpriteID);
}
