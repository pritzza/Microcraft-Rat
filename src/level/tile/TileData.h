#pragma once

#include "../../gfx/sheet/SpriteSheetAnimationData.h"
#include "../../gfx/color/ColorPalette.h"

// TileData is a data structure that stores data that every
// every TileBase and TileFeature will inherit from
struct TileData
{
public:
	static constexpr int DIMENSION{ 2 };
	static constexpr int NUM_COMPONENTS{ DIMENSION * DIMENSION };

public:
	AnimatedSpriteID borderAnimatedSpriteID;
	AnimatedSpriteID flavorAnimatedSpriteID;
	ColorPalette colorPalette;

private:
	TileData(const AnimatedSpriteID borderAnimatedSpriteID, 
		const AnimatedSpriteID flavorAnimatedSpriteID,
		const ColorPalette colorPalette)
		:
		borderAnimatedSpriteID{ borderAnimatedSpriteID },
		flavorAnimatedSpriteID{ flavorAnimatedSpriteID },
		colorPalette{ colorPalette }
	{}

	// TileData should only be apart of Tile___Data classes
	friend struct TileBaseData;
	friend struct TileFeatureData;

	// Also needs to be constructed in Tile___ for tilebases and tilefeatures
	friend struct TileBase;
	friend struct TileFeature;
};
