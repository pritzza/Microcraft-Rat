#pragma once

#include "tile/Tile.h"

#include "../util/AABB.h"
#include "../util/Vector.h"

#include "../gfx/sprite/Sprite.h"

#include <cstdint>

struct Vec2i;

// simple data structure to store "chunks" of tiles/tileIDs in LEN*LEN sized array

// when uncommenting stuff about structures, be sure to update them to be the same as tiles
struct Chunk
{
public:
	static constexpr uint8_t LENGTH{ 8 };
	static constexpr uint16_t SIZE{ LENGTH * LENGTH };

public:
	Tile tiles[SIZE];

public:
	Chunk(const int seed = 0);

	// getters
	Tile& getTile(const uint16_t i)										{ return tiles[i];							  					  }
	Tile& getTile(const Vec2i& coords)									{ return tiles[Vec2i::toIndex(coords, LENGTH, LENGTH)];			  }
	const Tile& getTile(const uint16_t i) const							{ return tiles[i];							  					  }
	const Tile& getTile(const Vec2i& coords) const						{ return tiles[Vec2i::toIndex(coords, LENGTH, LENGTH)];			  }

	inline static constexpr int getLength() { return LENGTH; }
	inline static constexpr int getSize()	{ return SIZE;	 }

	// returns length of chunk in pixels
	inline static constexpr int getPixelLength() 
	{
		return LENGTH * TileData::DIMENSION * SpriteSheetData::getTileLength();
	}

	// returns bounding box of chunk
	inline static constexpr AABB getAABB(const Vec2i& coords)
	{
		const Vec2i startPos{ coords * Chunk::getPixelLength() };
		const Vec2i dimensions{ Chunk::getPixelLength(), Chunk::getPixelLength() };

		return AABB{ startPos.x, startPos.y, dimensions.x, dimensions.y };
	}

};