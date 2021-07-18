#pragma once

#include "../gfx/sprite/SpriteSheet.h"
#include "../gfx/color/ColorPalette.h"

struct Tile
{
public:
	// when one tile is drawn, it is actually made up of 2x2 sprites
	static constexpr int SPRITE_DIMENSIONS{ 2 };

public:
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
		Water,		// 2
		NumTiles
	};

private:
	// would be cool to make these constexpr somehow
	inline static const Tile tiles[static_cast<int>(TileID::NumTiles)]
	{
		{ SpriteSheet::SpriteID::GroundTile, ColorPalette{433, 231, 232, 242} },	// grass 0
		{ SpriteSheet::SpriteID::GroundTile, ColorPalette{433, 222, 333, 444} },		// stone 1
		{ SpriteSheet::SpriteID::GroundTile, ColorPalette{433, 114, 225, 335} }		// water 2
	};

public:
	inline static const Tile& getTile(const TileID t)
	{
		return tiles[static_cast<int>(t)];
	}
};