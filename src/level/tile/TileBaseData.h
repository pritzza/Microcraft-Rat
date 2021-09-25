#pragma once

#include "TileData.h"

struct TileBaseData : public TileData
{
public:
	const bool hasFlavors;
	const bool isFluid;
	const bool canSpriteFlipHorizontally;
	const bool isGlobalAnimation;

private:
	TileBaseData(const AnimatedSpriteID animatedSpriteID, const ColorPalette colorPalette, 
		const bool hasFlavors,
		const bool isFluid,
		const bool canSpriteFlipHorizontally,
		const bool isGlobalAnimation
	)
		:
		TileData{ animatedSpriteID, colorPalette },
		hasFlavors{ hasFlavors },
		isFluid{ isFluid },
		canSpriteFlipHorizontally{ canSpriteFlipHorizontally },
		isGlobalAnimation{ isGlobalAnimation }
	{}

	friend struct TileBase;	// Tiles is the only place where Tile should be made
};
