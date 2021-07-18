#include "Chunk.h"

#include "../util/Random.h"

#include "../util/Vector.h"

Chunk::Chunk()
{
	Random rng;

	static constexpr int NUM_TILES{ static_cast<int>(Tiles::TileID::NumTiles) };

	// default initialize tileData to grass so we never have any nullptr nonsense
	for (int i = 0; i < this->SIZE; ++i)
	{
		this->setTile(i, static_cast<Tiles::TileID>( rng.getNum(0, NUM_TILES - 1) ));
	}
}

// setters
void Chunk::setTile(const uint16_t i, const Tiles::TileID data)
{
	if (i < SIZE)
		this->tileData[i] = data;
}

void Chunk::setTile(const Vec2i& coords, const Tiles::TileID data)
{
	this->setTile(Vec2i::toIndex(coords, Chunk::LENGTH, Chunk::LENGTH), data);
}

//void Chunk::setStructure(const uint16_t i, const Structure& data)
//{
//	if (i < SIZE)
//		this->structureData[i] = data;
//}
//
//void Chunk::setStructure(const uint8_t x, const uint8_t y, const Structure& data)
//{
//	this->setStructure(x + (y * LENGTH), data);
//}

// getters
const Tiles::TileID Chunk::getTileID(const uint16_t i) const
{
	if (i < SIZE)
		return this->tileData[i];

	return this->tileData[0];
}

const Tiles::TileID Chunk::getTileID(const Vec2i& coords) const
{
	return getTileID(coords.x + (coords.y * LENGTH));
}

//const Structure Chunk::getStructure(const uint16_t i) const
//{
//	if (i < SIZE)
//		return this->structureData[i];
//
//	return this->structureData[0];
//}
//
//const Structure Chunk::getStructure(const uint8_t x, const uint8_t y) const
//{
//	return getStructure(x + (y * LENGTH));
//}
