#include "World.h"

#include "../util/Direction.h"

#include <iostream>

void World::loadChunk(const Vec2i& pos)
{
	// probably pass the seed into the chunk later when doing world gen
	this->chunks.insert(std::pair{ pos, Chunk{} });
}

void World::unloadChunk(const Vec2i& pos)
{
}

const Vec2i World::getChunkPos(const Vec2i& chunkPos, const Vec2i& tilePos, const Vec2i& tileOffset) const
{
	Vec2i newChunkPos{ chunkPos };
	Vec2i newTilePos{ tilePos + tileOffset };
	//
	//if (newTilePos.x < 0)
	//	newChunkPos.x -= (1 + (newTilePos.x / Chunk::getLength()));
	//if (newTilePos.y < 0)
	//	newChunkPos.y -= (1 + (newTilePos.y / Chunk::getLength()));

	newChunkPos += (newTilePos) / Chunk::getLength();

	return newChunkPos;
}

const Vec2i World::getTilePos(const Vec2i& tilePos, const Vec2i& tileOffset) const
{
	Vec2i newTilePos{ tilePos + tileOffset };

	//if (newTilePos.x < 0)
	//	newTilePos.x += Chunk::getLength() * (1 + (newTilePos.x / Chunk::getLength()));
	//if (newTilePos.y < 0)
	//	newTilePos.y += Chunk::getLength() * (1 + (newTilePos.y / Chunk::getLength()));

	newTilePos %= Chunk::getLength();

	return newTilePos;
}

const DetailedDirection World::getTileDirection(const Vec2i& chunkPos, const Vec2i& tilePos, const int tileSpriteIndex) const
{
	// if the chunk containing the tile isnt loaded, return this TileCrop
	static constexpr DetailedDirection DEFAULT_TILE_CROP{ DetailedDirection::Center };

	if (this->chunks.find(chunkPos) == this->chunks.end())
		return DEFAULT_TILE_CROP;
	else
	{
		DetailedDirection direction{ DetailedDirection::Center };

		const Tiles::TileID baseTileID{ this->chunks.at(chunkPos).getTileID(tilePos) };

		static constexpr int TILE_DIM{ Tile::SPRITE_DIMENSIONS };

		// * 2 so its its always between 0-2 and -1 so it becomes just 1's and -1's
		const Vec2i subTileSpriteOffset{ (Vec2i::toVector(tileSpriteIndex, TILE_DIM, TILE_DIM) * 2 ) - 1 };

		// we only care about the tiles directly above, below, left, and right of the checking tile
		for (int i = 0; i < Directions::NUM_DIRECTIONS; ++i)
		{
			const Vec2i adjacentTileDirection{ Directions::toVector(static_cast<Direction>(i)) };

			const Vec2i offset{ (adjacentTileDirection + subTileSpriteOffset) / 2 };

			const Vec2i adjacentTilesChunkPos{ this->getChunkPos(chunkPos, tilePos, offset) };
			const Vec2i adjacentTilesPos{ this->getTilePos(tilePos, offset) };

			if (
				this->chunks.find(adjacentTilesChunkPos) != this->chunks.end() &&
				baseTileID == chunks.at(adjacentTilesChunkPos).getTileID(adjacentTilesPos)
				)
				direction = Directions::subtract(direction, static_cast<Direction>(i));
		}

		return direction;
	}
}
