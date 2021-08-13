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

	// setters
	void setTile(const uint16_t i, const Tile& t)						{ tiles[i] = t;							  						  }
	void setTile(const Vec2i& coords, const Tile& t)					{ tiles[Vec2i::toIndex(coords, LENGTH, LENGTH)] = t;			  }

	void setTileBase(const uint16_t i, const TileBases::ID id)			{ tiles[i].baseID = id;											  }
	void setTileBase(const Vec2i& coords, const TileBases::ID id)		{ tiles[Vec2i::toIndex(coords, LENGTH, LENGTH)].baseID = id;      }

	void setTileFeature(const uint16_t i, const TileFeatures::ID id)	{ tiles[i].featureID = id;										  }
	void setTileFeature(const Vec2i& coords, const TileFeatures::ID id) { tiles[Vec2i::toIndex(coords, LENGTH, LENGTH)].featureID = id;	  }

	// getters
	Tile& getTile(const uint16_t i)										{ return tiles[i];							  					  }
	Tile& getTile(const Vec2i& coords)									{ return tiles[Vec2i::toIndex(coords, LENGTH, LENGTH)];			  }
	const Tile& getTile(const uint16_t i) const							{ return tiles[i];							  					  }
	const Tile& getTile(const Vec2i& coords) const						{ return tiles[Vec2i::toIndex(coords, LENGTH, LENGTH)];			  }

	const TileBases::ID getTileBaseID(const uint16_t i) const			{ return tiles[i].baseID;										  }
	const TileBases::ID getTileBaseID(const Vec2i& coords) const		{ return tiles[Vec2i::toIndex(coords, LENGTH, LENGTH)].baseID;    }

	const TileFeatures::ID getTileFeatureID(const uint16_t i) const		{ return tiles[i].featureID;									  }
	const TileFeatures::ID getTileFeatureID(const Vec2i& coords) const	{ return tiles[Vec2i::toIndex(coords, LENGTH, LENGTH)].featureID; }

	inline static constexpr int getLength() { return LENGTH; }
	inline static constexpr int getSize()	{ return SIZE;	 }

	// returns length of chunk in pixels
	inline static constexpr int getPixelLength() 
	{
		return LENGTH * TileData::DIMENSION * SpriteSheet::getTileLength();
	}

	// returns bounding box of chunk
	inline static constexpr AABB getAABB(const Vec2i& coords)
	{
		const Vec2i startPos{ coords * Chunk::getPixelLength() };
		const Vec2i dimensions{ Chunk::getPixelLength(), Chunk::getPixelLength() };

		return AABB{ startPos.x, startPos.y, dimensions.x, dimensions.y };
	}

};