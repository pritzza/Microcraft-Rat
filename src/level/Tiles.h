#pragma once

#include "../gfx/sprite/SpriteSheet.h"
#include "../gfx/color/ColorPalette.h"

struct Tile
{
	// ingame properties
	SpriteSheet::SpriteID spriteID;
	ColorPalette colorPalette;

	// there are going to be a finite number of different types of tiles, and the only
	// tiles we want to use should be known at compile time and a member of the Tiles class
	// no Tile should ever be made outside of Tiles
private:
	Tile(const SpriteSheet::SpriteID spriteID, const ColorPalette colorPalette)
		:
		spriteID{ spriteID },
		colorPalette{ colorPalette }
	{}

	friend struct Tiles;	// Tiles is the only place where Tile should be made
};

struct Tiles
{
private:
	// a tile is a bit of data structure that stores all of the data it takes
	// to represent a tile, including its ingame properties, and sprite/color data

public:
	// be sure to have a Tles::TileID and Tiles::tiles entry for every tile
	enum class TileID
	{
		Grass,		// 0
		Stone,		// 1
		NumTiles
	};

private:
	// would be cool to make these constexpr somehow
	inline static const Tile tiles[static_cast<int>(TileID::NumTiles)]
	{
		{ SpriteSheet::SpriteID::GroundTile, ColorPalette{131, 231, 232, 212} },	// grass 0
		{ SpriteSheet::SpriteID::GroundTile, ColorPalette{111, 222, 333, 444} }		// stone 1
	};

public:
	inline static const Tile& getTile(const TileID t)
	{
		return tiles[static_cast<int>(t)];
	}
};

// for getting corecctly cropped sprites of tiles
enum class TileCrop
{
	TopLeft,		// 0
	TopMiddle,		// 1
	TopRight,		// 2
	LeftMiddle,		// 3
	MiddleMiddle,	// 4
	RightMiddle,	// 5
	LeftBottom,		// 6
	MiddleBottom,	// 7
	RightBottom		// 8
};