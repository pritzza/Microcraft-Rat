#include "SpriteCropper.h"

#include "animation/AnimatedSprite.h"

#include "../sheet/SpriteSheetAnimationData.h"

#include "../../level/tile/Tile.h"
#include "../../level/World.h"

//TODOTODOTODO TODO NOW
// refactor everything here
const Vec2i SpriteCropper::getTileBaseOffset(const Tile& tile, const int compIndex, const World& world, const Vec2i& chunkCoords, const int tileIndex) const
{
	static constexpr int TILE_PIXEL_LENGTH{ SpriteSheetData::getTileLength() * Sprite::STANDARD_LENGTH };

	if (tile.getBase().isComponentBorder(compIndex))
	{
		const DetailedDirection tileDirection{ tile.getBase().directions[compIndex] };
		const Vec2i tileDirectionVector{ Directions::toVector(tileDirection) };

		return (SpriteSheetData::getTileCenterOffset() + tileDirectionVector) * TILE_PIXEL_LENGTH;
	}
	else
	{
		const Vec2i flavorBounds{ tile.getBase().flavorSprite.getAnimationBounds() };

		const int numFlavors{ flavorBounds.x * flavorBounds.y };

		const unsigned int flavorValue{
			(tile.getBase().randomNums[compIndex]  + tile.getBase().flavorSprite.getCurrentFrame()) % numFlavors
		};

		const Vec2i flavorAnimationOffsetVector{ Vec2i::toVector(flavorValue, flavorBounds.x, flavorBounds.y) };

		return flavorAnimationOffsetVector * TILE_PIXEL_LENGTH;
	}
}

const Vec2i SpriteCropper::getTileFeatureOffset(const Tile& tile, const int compIndex, const int featureSpriteLen) const
{
	static constexpr int TILE_PIXEL_LENGTH{ SpriteSheetData::getTileLength() * Sprite::STANDARD_LENGTH };

	const bool isFeatureFlavored{ tile.getFeature().getData().hasFlavors };
	
	if (isFeatureFlavored)
	{
		const Vec2i flavorBounds{ tile.getBase().flavorSprite.getAnimationBounds() };

		const int numFlavors{ flavorBounds.x * flavorBounds.y };

		const unsigned int flavorValue{
			(tile.getFeature().randomNums[compIndex] + tile.getFeature().flavorSprite.getCurrentFrame()) % numFlavors
		};

		return Vec2i::toVector(flavorValue, flavorBounds.x, flavorBounds.y);
	}

	return { 0, 0 };
}