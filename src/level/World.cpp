#include "World.h"

#include "../util/Direction.h"

#include "../gfx/Camera.h"

#include <iostream>

World::World(const int terrainSeed, const int tileSeed)
	:
	terrainSeed{ terrainSeed },
	tileFlavoringSeed{ tileSeed }
{
}

void World::update(const Camera& camera)
{
	// some aliases for more readability
	const Vec2i& camDim{ camera.getDimensions() };
	const Vec2i& camPos{ camera.getPos() };
	constexpr int chunkLen{ Chunk::getPixelLength() };

	static constexpr int LOAD_DISTANCE{ 2 };

	// the number of chunks that are loaded and being updated in the x and y axis around the camera
	const Vec2i chunksLoaded{ (camDim / chunkLen) + LOAD_DISTANCE };

	// if camera's coords are negative, they become off by 1 cause of some funky division
	const Vec2i negativeCompensation{ camPos.x < -chunkLen, camPos.y < -chunkLen/2 };

	const Vec2i centerChunk{ ((camPos + (camDim / 2)) / chunkLen) - negativeCompensation };

	// load surrounding chunks
	for (int x = 0; x < chunksLoaded.x; ++x)
		for (int y = 0; y < chunksLoaded.y; ++y)
		{
			const Vec2i inRangeChunkCoords
			{
				(centerChunk.x - (chunksLoaded.x / 2)) + x,
				(centerChunk.y - (chunksLoaded.y / 2)) + y + (camPos.y % chunkLen > chunkLen / 2)	// to accomidate the closer chunk
			};

			if (chunks.find(inRangeChunkCoords) == chunks.end())
				loadChunk(inRangeChunkCoords);
		}

	// update or unload further chunks
	for (const auto& [coords, chunk] : this->chunks)
	{
		const AABB chunkBounds
		{
			coords.x * Chunk::getPixelLength(),
			coords.y * Chunk::getPixelLength(),
			Chunk::getPixelLength() - 1,
			Chunk::getPixelLength() - 1
		};

		//if(AABB::isPointInside(coords,))
	}
}

void World::generateChunk(const Vec2i& chunkCoord)
{
	Chunk& chunk{ this->chunks.at(chunkCoord) };

	//this->perlinNoise.reseed(terrainSeed);

	// between 0.1 and 64
	static constexpr double FREQUENCY{ 8.f };

	const Vec2i tileOffset{ chunkCoord * Chunk::getLength() };

	double tileValue;

	for (int y = 0; y < Chunk::getLength(); ++y)
		for (int x = 0; x < Chunk::getLength(); ++x)
		{
			const Vec2i tileCoord{ x, y };

			static constexpr double WATER_MAX{ 0.4 };
			static constexpr double GRASS_MAX{ 0.7 };
			static constexpr double STONE_MAX{ 1 };

			tileValue = perlinNoise.noise2D_0_1((x + tileOffset.x) / FREQUENCY, (y + tileOffset.y) / FREQUENCY);

			if (tileValue < WATER_MAX)
				chunk.setTileBase(tileCoord, TileBases::ID::Water);
			else if (tileValue < GRASS_MAX)
				chunk.setTileBase(tileCoord, TileBases::ID::Grass);
			else if (tileValue < STONE_MAX)
				chunk.setTileBase(tileCoord, TileBases::ID::Stone);

			Tile& tile{ chunk.getTile(tileCoord) };

			for (int i = 0; i < TileData::NUM_COMPONENTS; ++i)
			{
				tile.flavors[i] = static_cast<TileFlavor::Value>(rng.getNum(0, TileFlavor::NUM_FLAVORS));

				if (tile.baseID == TileBases::ID::Grass)
				{
					// try to spawn flower
					if (rng.getNum(0, 8) == 0)
					{
						tile.featureID = TileFeatures::ID::Flower;
						tile.featurePlacement[i] = true;
					}

					// try to spawn tree
					if (rng.getNum(0, 8) == 0)
					{
						tile.featureID = TileFeatures::ID::Tree;
						tile.featurePlacement[i] = true;
					}
				}
			}
		}

	// attempt at assigning direction upon generating tile
	//for (int i = 0; i < TileData::NUM_COMPONENTS; ++i)
	//{
	//	Tile& tile{ chunk.getTile(i) };
	//
	//	const Vec2i tileCoord{ Vec2i::toVector(i, Chunk::getLength(), Chunk::getLength()) };
	//
	//	for (int j = 0; j < TileData::NUM_COMPONENTS; ++j)
	//		tile.directions[j] = this->getTileDirection(chunkCoord, tileCoord, j);
	//}
}

void World::loadChunk(const Vec2i& pos)
{
	// probably pass the seed into the chunk later when doing world gen
	this->chunks.insert(std::pair{ pos, Chunk{} });

	generateChunk(pos);
}

void World::unloadChunk(const Vec2i& pos)
{
	this->chunks.erase(pos);
}

const Vec2i World::getChunkPos(const Vec2i& chunkPos, const Vec2i& tilePos, const Vec2i& tileOffset) const
{
	Vec2i newChunkPos{ chunkPos };
	const Vec2i newTilePos{ tilePos + tileOffset };

	if (newTilePos.x < 0)
		newChunkPos.x -= (newTilePos.x / Chunk::getLength()) + 1;
	else
		newChunkPos.x += newTilePos.x / Chunk::getLength();

	if (newTilePos.y < 0)
		newChunkPos.y -= (newTilePos.y / Chunk::getLength()) + 1;
	else
		newChunkPos.y += newTilePos.y / Chunk::getLength();

	return newChunkPos;
}

const Vec2i World::getTilePos(const Vec2i& tilePos, const Vec2i& tileOffset) const
{
	Vec2i newTilePos{ tilePos + tileOffset };

	if (newTilePos.x < 0)
		newTilePos.x += ((newTilePos.x / Chunk::getLength()) + 1) * Chunk::getLength();
	else
		newTilePos.x %= Chunk::getLength();

	if (newTilePos.y < 0)
		newTilePos.y += ((newTilePos.y / Chunk::getLength()) + 1) * Chunk::getLength();
	else
		newTilePos.y %= Chunk::getLength();

	return newTilePos;
}

const DetailedDirection World::getTileDirection(const Vec2i& chunkPos, const Vec2i& tilePos, const int tileSpriteIndex) const
{
	// if the chunk containing the tile isnt loaded, return this TileCrop
	static constexpr DetailedDirection DEFAULT_TILE_CROP{ DetailedDirection::Center };


		DetailedDirection direction{ DetailedDirection::Center };

		const TileBases::ID baseTileID{ this->chunks.at(chunkPos).getTileBaseID(tilePos) };

		static constexpr int TILE_DIM{ TileData::DIMENSION };

		// * 2 so its its always between 0-2 and -1 so it becomes just 1's and -1's
		const Vec2i subTileSpriteOffset{ (Vec2i::toVector(tileSpriteIndex, TILE_DIM, TILE_DIM) * 2) - 1 };

		// we only care about the tiles directly above, below, left, and right of the checking tile
		for (int i = 0; i < Directions::NUM_DIRECTIONS; ++i)
		{
			const Vec2i adjacentTileDirection{ Directions::toVector(static_cast<Direction>(i)) };

			const Vec2i offset{ (adjacentTileDirection + subTileSpriteOffset) / 2 };

			const Vec2i adjacentTilesChunkPos{ this->getChunkPos(chunkPos, tilePos, offset) };
			const Vec2i adjacentTilesPos{ this->getTilePos(tilePos, offset) };

			if (
				this->chunks.find(adjacentTilesChunkPos) != this->chunks.end() &&
				baseTileID == chunks.at(adjacentTilesChunkPos).getTileBaseID(adjacentTilesPos)
				)
				direction = Directions::subtract(direction, static_cast<Direction>(i));
		}

		return direction;
	
}
