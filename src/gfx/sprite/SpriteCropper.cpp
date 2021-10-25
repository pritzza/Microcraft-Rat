#include "SpriteCropper.h"

#include "animation/AnimatedSprite.h"

#include "../sheet/SpriteSheetAnimationData.h"

#include "../../level/tile/Tile.h"
#include "../../level/World.h"

const Vec2i SpriteCropper::getTileBaseOffset(const Tile& tile, const int compIndex, const World& world, const Vec2i& chunkCoords, const int tileIndex) const
{
	static constexpr int TILE_LEN{ SpriteSheetData::getTileLength() };

	const TileBase& tileBase{ tile.getBase() };

	const DetailedDirection tileDirection{ tileBase.directions[compIndex] };

	const int flavorValue{ tileBase.flavors[compIndex].getValue() + tileBase.sprite.getCurrentFrame() };
	const bool isBaseFlavored{ (tileBase.flavors[compIndex].isFlavored() || tileBase.sprite.isAnimated()) && flavorValue };

	const TileFlavor animatedFlavor{ flavorValue, isBaseFlavored };

	// determines whether tile component should be cropped to have a flavor or a direction of a tile
	const bool cropTileBaseForFlavor
	{
		tileDirection == DetailedDirection::Center &&			// is a center tile
		animatedFlavor.isFlavored() &&							// has a flavor value
		tileBase.getData().hasFlavors							// tileBase supports flavors
	};

	// if the tile base has a flavor
	if (cropTileBaseForFlavor)
	{
		const Vec2i baseFlavorCropOffset{ Vec2i::toVector(animatedFlavor.getValue(), TileFlavor::DIMENSION, TileFlavor::DIMENSION) };

		// position of flavor sprite on spritesheet
		const Vec2i& baseFlavorSpritePos{ SpriteSheetData::getSpriteCoords(tileBase.getData().flavorSpriteID) };

		return baseFlavorSpritePos + baseFlavorCropOffset * TILE_LEN * Sprite::STANDARD_LENGTH;
	}
	else
		// otherwise, just give the crop based on the tile's direction
		return (Directions::toVector(tileDirection) + SpriteSheetData::getTileCenterOffset()) * TILE_LEN * Sprite::STANDARD_LENGTH;
}

const Vec2i SpriteCropper::getTileFeatureOffset(const Tile& tile, const int compIndex, const int featureSpriteLen) const
{
	const TileFeature& tileFeature{ tile.getFeature() };
	const AnimatedSprite& sprite{ tileFeature.sprite };

	// TODO proof check
	const TileFlavor animatedFlavor{
		tileFeature.flavors[compIndex].getValue()   +  tileFeature.sprite.getCurrentFrame(),
		tileFeature.flavors[compIndex].isFlavored() || tileFeature.sprite.isAnimated() 
	};

	const bool isFeatureFlavored{ tileFeature.getData().hasFlavors };

	if (isFeatureFlavored)
		return Vec2i::toVector(animatedFlavor.getValue(), TileData::DIMENSION, TileData::DIMENSION) * sprite.getDimensions().x;

	return { 0, 0 };
}

