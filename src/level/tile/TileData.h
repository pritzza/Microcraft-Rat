#pragma once

#include "../../gfx/sprite/SpriteSheet.h"
#include "../../gfx/color/ColorPalette.h"

// TileData is a data structure that stores data that every
// Base and Decoration will inherit from
// every TileBase and TileFeature
struct TileData
{
public:
	static constexpr int DIMENSION{ 2 };
	static constexpr int NUM_COMPONENTS{ DIMENSION * DIMENSION };

public:
	SpriteID spriteID;
	ColorPalette colorPalette;

private:
	TileData(const SpriteID spriteID, const ColorPalette colorPalette)
		:
		spriteID{spriteID},
		colorPalette{colorPalette}
	{}

	friend struct TileBaseData;
	friend struct TileFeatureData;
};
