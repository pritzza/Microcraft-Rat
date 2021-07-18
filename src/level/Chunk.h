#pragma once

#include <cstdint>
#include "../util/AABB.h"

#include "Tiles.h"

struct Vec2i;

// simple data structure to store "chunks" of tiles/tileIDs in LEN*LEN sized array

// when uncommenting stuff about structures, be sure to update them to be the same as tiles
struct Chunk
{
public:
	static constexpr uint8_t LENGTH{ 8 };
	static constexpr uint16_t SIZE{ LENGTH * LENGTH };

public:
	Tiles::TileID tileData[SIZE];
	//Structure* structureData[SIZE];

public:
	Chunk();

	// setters
	void setTile(const uint16_t i, const Tiles::TileID data);
	void setTile(const Vec2i& coords, const Tiles::TileID data);

	//void setStructure(const uint16_t i, const Structure& data);
	//void setStructure(const uint8_t x, const uint8_t y, const Structure& data);

	// getters
	const Tiles::TileID getTileID(const uint16_t i) const;
	const Tiles::TileID getTileID(const Vec2i& coords) const;

	//const Structure& getStructure(const uint16_t i) const;
	//const Structure& getStructure(const uint8_t x, const uint8_t y) const;

	inline static constexpr int getLength() { return LENGTH; }
	inline static constexpr int getSize()	{ return SIZE;	 }

};