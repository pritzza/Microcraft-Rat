#pragma once

#include "TileFeatureData.h"

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
	AnimatedSprite borderSprite;
	AnimatedSprite flavorSprite;

	DetailedDirection directions[TileData::NUM_COMPONENTS] = { DetailedDirection::Center };

	// TODO generate this during world gen, currently UB
	unsigned int randomNums[TileData::NUM_COMPONENTS]; // used for flavoring and other random stuff

	bool isOnComponent[TileData::NUM_COMPONENTS] = { true };

private:
	inline static const TileFeatureData tileFeatures[static_cast<int>(ID::NumFeatures)]
	{
		// BorderAnimatedSpriteID, FlavorAnimatedSpriteID, ColorPalette, hasFlavor, isSolid, isPlaceableOnEdges, isSmall, canSpriteFlipHorizontally, canPartiallyOccupyComponents
		{ TileData{ AnimatedSpriteID::EmptyTileFeature, AnimatedSpriteID::EmptyTileFeature,		ColorPalette(  0,   0,   0,   0 ) }, false, false, false, false, false, false, false },	// none   0
		{ TileData{ AnimatedSpriteID::DancingFlower,	AnimatedSpriteID::DancingFlower,		ColorPalette( -1, 223, 445, 550 ) }, true,  false, false, true , true,  true,  true  },	// flower 1
		{ TileData{ AnimatedSpriteID::Tree,				AnimatedSpriteID::Tree,					ColorPalette( -1, 321, 121, 131 ) }, false, false, true,  false, false, false, false },	// tree   2
	};

public:
	TileFeature(const ID id);

	bool isComponentBorder(const int compIndex) const 
	{
		return directions[compIndex] != DetailedDirection::Center; 
	}

	const bool isEmpty() const { return id == ID::None; }

	const TileFeatureData& getData() const
	{
		return tileFeatures[static_cast<int>(id)];
	}
};