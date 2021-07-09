#include "Chunk.h"

Chunk::Chunk()
{
	// default initialize tileData to grass so we never have any nullptr nonsense
	for (int i = 0; i < this->SIZE; ++i)
	{
		if (i%3)
			this->setTile(i, Tiles::Grass);
		else
			this->setTile(i, Tiles::Stone);
	}
}

// setters
void Chunk::setTile(const uint16_t i, const Tile& data)
{
	if (i < SIZE)
		this->tileData[i] = &data;
}

void Chunk::setTile(const uint8_t x, const uint8_t y, const Tile& data)
{
	this->setTile(x + (y * LENGTH), data);
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
const Tile& Chunk::getTile(const uint16_t i) const
{
	if (i < SIZE)
		return *this->tileData[i];

	return *this->tileData[0];
}

const Tile& Chunk::getTile(const uint8_t x, const uint8_t y) const
{
	return getTile(x + (y * LENGTH));
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
