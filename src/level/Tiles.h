#pragma once

#include "../gfx/SpriteSheet.h"
#include "../gfx/ColorPalette.h"

// a tile is a bit of data structure that stores all of the data it takes
// to represent a tile, including its ingame properties, and sprite/color data
struct Tile
{
	// ingame properties
	SpriteSheet::SpriteID spriteID;
	ColorPalette colorPalette;

	// there are going to be a finite number of different types of tiles, and the only
	// tiles we want to use should be known at compile time and a member of the Tiles class
private:
	Tile(const SpriteSheet::SpriteID spriteID, const ColorPalette colorPalette)
		:
		spriteID{ spriteID },
		colorPalette{ colorPalette }
	{}

	friend struct Tiles;
};

// all of the tiles in the game
struct Tiles
{
	// would be cool to make these constexpr somehow
	inline static const Tile Grass{ SpriteSheet::SpriteID::GroundTile, ColorPalette{131, 131, 212, 212} };
	inline static const Tile Stone{ SpriteSheet::SpriteID::GroundTile, ColorPalette{111, 222, 333, 444} };
};