#pragma once

#include "../../gfx/sprite/SpriteSheet.h"
#include "../../gfx/color/ColorPalette.h"

// TileData is a data structure that stores data that every
// Base and Decoration will inherit from
// every TileBase and TileFeature
struct TileData
{
public:
	static constexpr int SPRITE_DIMENSIONS{ 2 };

public:
	SpriteSheet::SpriteID spriteID;
	ColorPalette colorPalette;

private:
	TileData(const SpriteSheet::SpriteID spriteID, const ColorPalette colorPalette)
		:
		spriteID{spriteID},
		colorPalette{colorPalette}
	{}

	friend struct TileBaseData;
	friend struct TileFeatureData;
};
