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
		//	SpriteID, ColorPalette, animationTickRate, hasFlavor, isSolid, isPlaceableOnEdges, isSmall
		{ SpriteID::Sprite,					ColorPalette{ 1000,1000,1000,1000 }, 0.0f, false, false, false, false },	// none   0
		{ SpriteID::FlowerTileFeatureStart, ColorPalette{ 1000, 223, 445, 550 }, 0.0f, true,  false, false, true  },	// flower 1
		{ SpriteID::TreeTileFeatureStart,   ColorPalette{ 1000, 321, 121, 131 }, 0.0f, false, false, true,  false },	// tree   2
	};

public:
	inline static const TileFeatureData& getFeature(const ID t)
	{
		return tileFeatures[static_cast<int>(t)];
	}
};