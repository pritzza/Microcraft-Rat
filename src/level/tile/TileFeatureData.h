#pragma once

#include "TileData.h"

struct TileFeatureData : public TileData
{
public:
	bool isSolid;
	//int height
	// Tool toolToBreak;

private:
	TileFeatureData(const SpriteSheet::SpriteID spriteID, const ColorPalette colorPalette,
		const bool isSolid)
		:
		TileData{ spriteID, colorPalette },
		isSolid{ isSolid }
	{}

	friend struct TileFeatures;	// Tiles is the only place where Tile should be made
};
