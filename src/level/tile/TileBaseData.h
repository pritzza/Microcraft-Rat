#pragma once

#include "TileData.h"

struct TileBaseData : public TileData
{
public:
	bool hasFlavors;
	bool isFluid;

private:
	TileBaseData(const SpriteSheet::SpriteID spriteID, const ColorPalette colorPalette, 
		const bool hasFlavors,
		const bool isFluid)
		:
		TileData{ spriteID, colorPalette },
		hasFlavors{ hasFlavors },
		isFluid{ isFluid }
	{}

	friend struct TileBases;	// Tiles is the only place where Tile should be made
};
