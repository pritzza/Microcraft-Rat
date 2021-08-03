#pragma once

#include "TileData.h"

struct TileBaseData : public TileData
{
public:
	bool isFluid;

private:
	TileBaseData(const SpriteSheet::SpriteID spriteID, const ColorPalette colorPalette, 
		const bool isFluid)
		:
		TileData{ spriteID, colorPalette },
		isFluid{ isFluid }
	{}

	friend struct TileBases;	// Tiles is the only place where Tile should be made
};
