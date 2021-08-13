#pragma once

#include "TileData.h"

struct TileFeatureData : public TileData
{
public:
	bool hasFlavors;
	bool isSolid;
	bool isPlaceableOnEdges;
	bool isSmall;		// isnt very dynamic, but features can basically only be 1x1 or 2x2 tile components large so far
	//int height
	// Tool toolToBreak;

	double animationTickRate;	// rate at which the flavor is incrimented (if it has one) in seconds

private:
	TileFeatureData(const SpriteID spriteID, const ColorPalette colorPalette,
		const double animationTickRate,
		const bool hasFlavors,
		const bool isSolid,
		const bool isPlaceableOnEdges,
		const bool isSmall)
		:
		TileData{ spriteID, colorPalette },
		animationTickRate{ animationTickRate },
		hasFlavors{ hasFlavors },
		isSolid{ isSolid },
		isPlaceableOnEdges{ isPlaceableOnEdges },
		isSmall{ isSmall }
	{}

	friend struct TileFeatures;	// Tiles is the only place where Tile should be made
};
