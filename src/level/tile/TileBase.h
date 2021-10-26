#pragma once

#include "TileBaseData.h"

struct TileBase
{
public:
	// be sure to have a Tles::TileID and Tiles::tiles entry for every tile
	enum class ID
	{
		Grass,		// 0
		Stone,		// 1
		Water,		// 2

		NumTiles
	};

	ID id;
	AnimatedSprite borderSprite;	// store sprite for tile borders
	AnimatedSprite flavorSprite;	// store sprite for tile flavors (non border)

	DetailedDirection directions[TileData::NUM_COMPONENTS] = { DetailedDirection::Center };

	// TODO generate this during world gen, currently UB
	unsigned int randomNums[TileData::NUM_COMPONENTS]; // used for flavoring and other random stuff

private:
	// would be cool to make these constexpr somehow
	inline static const TileBaseData tileBases[static_cast<int>(ID::NumTiles)]
	{
	//    TileData{ BorderAnimatedSpriteID, FlavorAnimatedSpriteID, ColorPalette }, hasFlavor, isFluid, canSpriteFlipHorizontally
		{ TileData{ AnimatedSpriteID::UnAnimatedGroundTileBase, AnimatedSpriteID::UnAnimatedGroundFlavor,	ColorPalette{ 433, 121, 232, 242 } }, true, false, true,  true },	// grass 0
		{ TileData{ AnimatedSpriteID::UnAnimatedGroundTileBase, AnimatedSpriteID::UnAnimatedGroundFlavor,	ColorPalette{ 433, 222, 333, 444 } }, true, false, false, true },	// stone 1
		{ TileData{ AnimatedSpriteID::UnAnimatedGroundTileBase,	AnimatedSpriteID::Water,					ColorPalette{ 433, 114, 225, 335 } }, true, true , false, true }	// water 2
	};

public:
	TileBase(const ID id);

	bool isComponentBorder(const int compIndex) const 
	{
		return directions[compIndex] != DetailedDirection::Center; 
	}

	const TileBaseData& getData() const 
	{
		return tileBases[static_cast<int>(id)]; 
	}
};