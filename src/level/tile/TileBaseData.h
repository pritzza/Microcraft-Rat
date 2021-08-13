#pragma once

#include "TileData.h"

struct TileBaseData : public TileData
{
public:
	bool hasFlavors;
	bool isFluid;

	double animationTickRate;	// rate at which the flavor is incrimented (if it has one) in seconds

private:
	TileBaseData(const SpriteID spriteID, const ColorPalette colorPalette, 
		const double animationTickRate,
		const bool hasFlavors,
		const bool isFluid)
		:
		TileData{ spriteID, colorPalette },
		animationTickRate{ animationTickRate },
		hasFlavors{ hasFlavors },
		isFluid{ isFluid }
	{}

	friend struct TileBases;	// Tiles is the only place where Tile should be made
};
