#pragma once

#include "TileData.h"

struct TileFeatureData : public TileData
{
public:
	bool hasFlavors;

	bool isSolid;
	bool isPlaceableOnEdges;
	bool isSmall;		// isnt very dynamic, but features can basically only be 1x1 or 2x2 tile components large so far
	bool canSpriteFlipHorizontally;
	bool isGlobalAnimation;
	bool canPartiallyOccupyComponents;

	//int height
	// Tool toolToBreak;

private:
	TileFeatureData(const TileData& tileData,
		const bool hasFlavors,
		const bool isSolid,
		const bool isPlaceableOnEdges,
		const bool isSmall,
		const bool canSpriteFlipHorizontally,
		const bool isGlobalAnimation,
		const bool canPartiallyOccupyComponents
	)
		:
		TileData{ tileData },
		hasFlavors{ hasFlavors },
		isSolid{ isSolid },
		isPlaceableOnEdges{ isPlaceableOnEdges },
		isSmall{ isSmall },
		canSpriteFlipHorizontally{ canSpriteFlipHorizontally },
		isGlobalAnimation{ isGlobalAnimation },
		canPartiallyOccupyComponents{ canPartiallyOccupyComponents }
	{}

	friend struct TileFeature;	// Tiles is the only place where Tile should be made
};
