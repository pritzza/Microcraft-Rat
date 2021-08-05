#pragma once

#include "TileBaseData.h"

struct TileBases
{
public:
	// be sure to have a Tles::TileID and Tiles::tiles entry for every tile
	enum class ID
	{
		Grass,		// 0
		Stone,		// 1
		Water,		// 2
		NumTiles
	};

private:
	// would be cool to make these constexpr somehow
	inline static const TileBaseData tileBases[static_cast<int>(ID::NumTiles)]
	{
		//	SpriteID, ColorPalette, hasFlavor, isFluid
		{ SpriteSheet::SpriteID::GroundTileBaseStart, ColorPalette{433, 121, 232, 242}, true, false },	// grass 0
		{ SpriteSheet::SpriteID::GroundTileBaseStart, ColorPalette{433, 222, 333, 444}, true, false },	// stone 1
		{ SpriteSheet::SpriteID::GroundTileBaseStart, ColorPalette{433, 114, 225, 335}, true, true  }	// water 2
	};

public:
	inline static const TileBaseData& getBase(const ID t)
	{
		return tileBases[static_cast<int>(t)];
	}
};