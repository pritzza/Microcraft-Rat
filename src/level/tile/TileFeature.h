#pragma once

#include "TileFeatureData.h"
#include "TileFlavor.h"

struct TileFeature
{
public:
	enum class ID
	{
		None,			// 0
		Flower,			// 1
		Tree,			// 2

		NumFeatures
	};

	ID id;
	AnimatedSprite sprite;

	DetailedDirection directions[TileData::NUM_COMPONENTS] = { DetailedDirection::Center };
	TileFlavor flavors[TileData::NUM_COMPONENTS] = { false, false, false, false };	// initialize all flavors to not be shown
	bool isOnComponent[TileData::NUM_COMPONENTS] = { false };

private:
	inline static const TileFeatureData tileFeatures[static_cast<int>(ID::NumFeatures)]
	{
		//	AnimatedSpriteID, ColorPalette, hasFlavor, isSolid, isPlaceableOnEdges, isSmall, canSpriteFlipHorizontally
		{ AnimatedSpriteID::EmptyTileFeature,	ColorPalette(  0,   0,   0,   0 ), false, false, false, false, false, true },	// none   0
		{ AnimatedSpriteID::DancingFlower,		ColorPalette( -1, 223, 445, 550 ), true,  false, false, true , true,  true },	// flower 1
		{ AnimatedSpriteID::Tree,				ColorPalette( -1, 321, 121, 131 ), false, false, true,  false, false, true },	// tree   2
	};

public:
	TileFeature(const ID id);

	const bool isEmpty() const { return id == ID::None; }

	const TileFeatureData& getData() const
	{
		return tileFeatures[static_cast<int>(id)];
	}
};