#pragma once

#include "TileFeatureData.h"

struct TileFeatures
{
public:
	enum class ID
	{
		None,			// 0
		Flower,			// 1
		Tree,			// 2
		NumFeatures
	};

private:
	inline static const TileFeatureData tileFeatures[static_cast<int>(ID::NumFeatures)]
	{
		//	SpriteID, ColorPalette, hasFlavor, isSolid, isPlaceableOnEdges, isSmall
		{ SpriteSheet::SpriteID::GroundTileBaseStart,	 ColorPalette { 1000,1000,1000,1000 }, false, false, false, false },	// none   0
		{ SpriteSheet::SpriteID::FlowerTileFeatureStart, ColorPalette { 1000, 223, 445, 550 }, true,  false, false, true  },	// flower 1
		{ SpriteSheet::SpriteID::TreeTileFeatureStart,   ColorPalette { 1000, 321, 131, 242 }, false, false, true,  false },	// tree   2
	};

public:
	inline static const TileFeatureData& getFeature(const ID t)
	{
		return tileFeatures[static_cast<int>(t)];
	}
};