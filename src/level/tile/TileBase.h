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
	TileFlavor flavors[TileData::NUM_COMPONENTS] = { true, true, true, true };	// show flavor on all components by default

private:
	// would be cool to make these constexpr somehow
	inline static const TileBaseData tileBases[static_cast<int>(ID::NumTiles)]
	{
		//	TileData{ AnimatedSpriteID, SpriteID, ColorPalette }, hasFlavor, isFluid, canSpriteFlipHorizontally
		{ TileData{ AnimatedSpriteID::UnAnimatedGroundTileBase, ColorPalette{ 433, 121, 232, 242 } }, SpriteID::GroundTileBaseFeature, true, false, true,  true },	// grass 0
		{ TileData{ AnimatedSpriteID::UnAnimatedGroundTileBase, ColorPalette{ 433, 222, 333, 444 } }, SpriteID::GroundTileBaseFeature, true, false, false, true },	// stone 1
		{ TileData{ AnimatedSpriteID::Water,					ColorPalette{ 433, 114, 225, 335 } }, SpriteID::GroundTileBaseFeature, true, true , false, true }	// water 2
	};

public:
	TileBase(const ID id);

	const TileBaseData& getData() const 
	{
		return tileBases[static_cast<int>(id)]; 
	}
};