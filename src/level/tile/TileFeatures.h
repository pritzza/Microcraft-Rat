#pragma once

#include "TileFeatureData.h"

struct TileFeatures
{
public:
	enum class ID
	{
		None,			// 0
		Flower,			// 1
		NumDecorations
	};

private:
	inline static const TileFeatureData tileFeatures[static_cast<int>(ID::NumDecorations)]
	{
		{ SpriteSheet::SpriteID::GroundTileBase,	 ColorPalette { 999, 999, 999, 999 }, false },	// none 0
		{ SpriteSheet::SpriteID::FlowerTileFeature,	 ColorPalette { 440, 330, 556, 999 }, false },	// flower 1
	};

public:
	inline static const TileFeatureData& getFeature(const ID t)
	{
		return tileFeatures[static_cast<int>(t)];
	}
};