#pragma once

#include <cstdint>
#include "../util/AABB.h"

#include "Tiles.h"

struct Chunk
{
public:
	static constexpr uint8_t LENGTH{ 16 };
	static constexpr uint16_t SIZE{ LENGTH * LENGTH };

public:
	const Tile* tileData[SIZE];
	//Structure* structureData[SIZE];

public:
	Chunk();

	// setters
	void setTile(const uint16_t i, const Tile& data);
	void setTile(const uint8_t x, const uint8_t y, const Tile& data);

	//void setStructure(const uint16_t i, const Structure& data);
	//void setStructure(const uint8_t x, const uint8_t y, const Structure& data);

	// getters
	const Tile& getTile(const uint16_t i) const;
	const Tile& getTile(const uint8_t x, const uint8_t y) const;

	//const Structure& getStructure(const uint16_t i) const;
	//const Structure& getStructure(const uint8_t x, const uint8_t y) const;

	inline static constexpr int getLength() { return LENGTH; }
	inline static constexpr int getSize()	{ return SIZE;	 }

};