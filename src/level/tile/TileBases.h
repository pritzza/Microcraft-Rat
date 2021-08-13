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
		//	SpriteID, ColorPalette, animationTickRate, hasFlavor, isFluid
		{ SpriteID::GroundTileBaseStart, ColorPalette{433, 121, 232, 242}, 0.f, true, false },	// grass 0
		{ SpriteID::GroundTileBaseStart, ColorPalette{433, 222, 333, 444}, 0.f, true, false },	// stone 1
		{ SpriteID::GroundTileBaseStart, ColorPalette{433, 114, 225, 335}, 1.f, true, true  }	// water 2
	};

public:
	inline static const TileBaseData& getBase(const ID t)
	{
		return tileBases[static_cast<int>(t)];
	}
};