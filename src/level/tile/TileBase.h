#pragma once

#include "TileBaseData.h"
#include "TileFlavor.h"

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
	AnimatedSprite sprite;

	DetailedDirection directions[TileData::NUM_COMPONENTS] = { DetailedDirection::Center };
	TileFlavor flavors[TileData::NUM_COMPONENTS] = { true, true, true, true };

private:
	// would be cool to make these constexpr somehow
	inline static const TileBaseData tileBases[static_cast<int>(ID::NumTiles)]
	{
		//	SpriteID, ColorPalette, hasFlavor, isFluid, canSpriteFlipHorizontally
		{ AnimatedSpriteID::UnAnimatedGroundTileBase,	ColorPalette{ 433, 121, 232, 242 }, true, false, true,  true },	// grass 0
		{ AnimatedSpriteID::UnAnimatedGroundTileBase,	ColorPalette{ 433, 222, 333, 444 }, true, false, false, true },	// stone 1
		{ AnimatedSpriteID::Water,						ColorPalette{ 433, 114, 225, 335 }, true, true , false, true }	// water 2
	};

public:
	TileBase(const ID id);

	const TileBaseData& getData() const 
	{
		return tileBases[static_cast<int>(id)]; 
	}

};