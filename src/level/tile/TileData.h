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
	AnimatedSpriteID animatedSpriteID;
	ColorPalette colorPalette;

private:
	TileData(const AnimatedSpriteID animatedSpriteID, const ColorPalette colorPalette)
		:
		animatedSpriteID{ animatedSpriteID },
		colorPalette{ colorPalette }
	{}

	friend struct TileBaseData;
	friend struct TileFeatureData;
};
