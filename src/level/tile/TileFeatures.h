#pragma once

#include "TileFeatureData.h"

struct TileFeatures
{
public:
	enum class ID
	{
		None,			// 0
		Flower,			// 1
		NumFeatures
	};

private:
	inline static const TileFeatureData tileFeatures[static_cast<int>(ID::NumFeatures)]
	{
		//	SpriteID, ColorPalette, hasFlavor, isSolid, isPlaceableOnEdges, isSmall
		{ SpriteSheet::SpriteID::GroundTileBaseStart,	 ColorPalette { 1000,1000,1000,1000 }, false, false, false, false },	// none 0
		{ SpriteSheet::SpriteID::FlowerTileFeatureStart, ColorPalette { 1000, 556, 440, 550 }, true,  false, false, true  },	// flower 1
	};

public:
	inline static const TileFeatureData& getFeature(const ID t)
	{
		return tileFeatures[static_cast<int>(t)];
	}
};