#pragma once

#include "TileData.h"

struct TileBaseData : public TileData
{
public:
	SpriteID flavorSpriteID;
	bool hasFlavors;

	bool isFluid;
	bool canSpriteFlipHorizontally;
	bool isGlobalAnimation;

private:
	TileBaseData(const TileData& tileData,
		const SpriteID flavorSpiteID,
		const bool hasFlavors,
		const bool isFluid,
		const bool canSpriteFlipHorizontally,
		const bool isGlobalAnimation
	)
		:
		TileData{ tileData },
		flavorSpriteID{ flavorSpriteID },
		hasFlavors{ hasFlavors },
		isFluid{ isFluid },
		canSpriteFlipHorizontally{ canSpriteFlipHorizontally },
		isGlobalAnimation{ isGlobalAnimation }
	{}

	friend struct TileBase;	// Tiles is the only place where Tile should be made
};
