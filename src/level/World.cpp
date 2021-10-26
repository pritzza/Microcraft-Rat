#include "World.h"

#include "generation/WorldGenerator.h"

#include "../gfx/Camera.h"

#include "../util/Direction.h"

void World::update(const double dt, const Camera& camera)
{
	// TODO maybe add option somewhere to change load distance
	static constexpr int LOAD_DISTANCE{ 2 };

	this->loadSurroundingChunks(camera, LOAD_DISTANCE);
	this->unloadOutOfViewChunks(camera, LOAD_DISTANCE);

	time += dt;

	for (auto& [coord, chunk] : this->chunks)
		for (int i = 0; i < Chunk::getSize(); ++i)
			chunk.getTile(i).update(time);
}

void World::loadSurroundingChunks(const Camera& camera, const int loadDistance)
{
	// some aliases for more readability
	const Vec2i& camDim{ camera.getDimensions() };
	const Vec2i& camPos{ camera.getPos() };
	constexpr int chunkLen{ Chunk::getPixelLength() };

	// the number of chunks that are loaded and being updated in the x and y axis around the camera
	const Vec2i chunksLoaded{ (camDim / chunkLen) + loadDistance };

	// if camera's coords are negative, they become off by 1 cause of some funky division
	const Vec2i negativeCompensation{ camPos.x < -chunkLen, camPos.y < -chunkLen / 2 };

	const Vec2i centerChunk{ ((camPos + (camDim / 2)) / chunkLen) - negativeCompensation };

	// load surrounding chunks
	for (int x = 0; x < chunksLoaded.x; ++x)
		for (int y = 0; y < chunksLoaded.y; ++y)
		{
			const Vec2i surroundingChunkCoords
			{
				(centerChunk.x - (chunksLoaded.x / 2)) + x,
				(centerChunk.y - (chunksLoaded.y / 2)) + y + (camPos.y % chunkLen > chunkLen / 2)	// to accomidate the closer chunk
			};

			if (chunks.find(surroundingChunkCoords) == chunks.end())
				loadChunk(surroundingChunkCoords);
		}
}

void World::unloadOutOfViewChunks(const Camera& camera, const int loadDistance)
{
	// update or unload further chunks
	for (const auto& [coord, chunk] : this->chunks)
	{
		const AABB chunkBounds
		{
			coord.x * Chunk::getPixelLength(),
			coord.y * Chunk::getPixelLength(),
			Chunk::getPixelLength() - 1,
			Chunk::getPixelLength() - 1
		};

		//if(AABB::isPointInside(coords,))
	}
}

void World::updateTileDirections(const Vec2i& chunkCoord)
{
	// can only updateTileDirs for chunks that exist
	if (this->chunks.find(chunkCoord) != chunks.end())
	{
		Chunk& chunk{ chunks.at(chunkCoord) };

		// attempt at assigning direction upon generating tile
		for (int y = 0; y < Chunk::getLength(); ++y)
			for (int x = 0; x < Chunk::getLength(); ++x)
			{
				const Vec2i tileCoord{ x, y };
				Tile& tile{ chunk.getTile(tileCoord) };

				for (int i = 0; i < TileData::NUM_COMPONENTS; ++i)
				{
					tile.getBase().directions[i] = this->getTileDirection(chunkCoord, tileCoord, i);
					tile.getFeature().directions[i] = this->getTileDirection(chunkCoord, tileCoord, i);
				}
			}
	}
}

void World::loadChunk(const Vec2i& pos)
{
	// probably pass the seed into the chunk later when doing world gen
	this->chunks.insert(std::pair{ pos, Chunk{} });

	this->worldGen.generateChunk(pos, *this);

	// we also want to update the directions of the tile components on adjacent chunk BORDERS
	// TODO: this only updates all tile directions in adjacent chunks, ideally only the BORDER MOST tile comps need updating
	for (int x = -1; x <= Directions::SQRT_NUM_DET_DIRS; ++x)
		for (int y = -1; y <= Directions::SQRT_NUM_DET_DIRS; ++y)
		{
			const Vec2i adjacentChunkCoord{ x, y };
			updateTileDirections(pos + adjacentChunkCoord);
		}
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

const Vec2i World::getTileComponentPixelPos(const Vec2i& chunkCoord, const int tileIndex, const int tileComponentIndex) const
{
		static constexpr int SPRITE_LEN{ Sprite::STANDARD_LENGTH };
		static constexpr int TILE_LEN{ SpriteSheetData::getTileLength() };
		static constexpr int TILE_DIM{ TileData::DIMENSION };
		static constexpr int CHUNK_LEN{ Chunk::getLength() };

		// positional offset from chunk to chunk
		const Vec2i chunkOffset{ chunkCoord * CHUNK_LEN * TILE_DIM * TILE_LEN * SPRITE_LEN };

		// positional offset from tile to tile
		const Vec2i tileOffset{ Vec2i::toVector(tileIndex, CHUNK_LEN, CHUNK_LEN) * TILE_DIM * TILE_LEN * SPRITE_LEN };

		// positional offset from tile sprite to tile sprite (tile is made up for 4 sprites)
		const Vec2i tileSpriteOffset{ Vec2i::toVector(tileComponentIndex, TILE_DIM, TILE_DIM) * TILE_LEN * SPRITE_LEN };

		// final position
		return Vec2i{ chunkOffset + tileOffset + tileSpriteOffset };
}

const DetailedDirection World::getTileDirection(const Vec2i& chunkPos, const Vec2i& tilePos, const int compIndex) const
{
	DetailedDirection direction{ DetailedDirection::Center };

	const TileBase::ID baseTileID{ chunks.at(chunkPos).getTile(tilePos).getBase().id };

	static constexpr int TILE_DIM{ TileData::DIMENSION };

		// what we do here is the check the 4 tiles adjacent to this one
		// if an adjacent tile has the same id, we subtract it
		// eg, if the tile north and east are the save, subtract north (0, -1), and east(1, 0)
		// you end up with a tile who's direction is southwest(1,1)

		// O is the tile we're checking, X is same type adjacent, you can see it should be bottomleft/southwest
		//
		//		X
		//		OX

	// * 2 so its its always between 0-2 and -1 so it becomes just 1's and -1's
	const Vec2i tileCompOffset{ (Vec2i::toVector(compIndex, TILE_DIM, TILE_DIM) * 2) - 1 };

	// we only care about the tiles directly above, below, left, and right of the checking tile
	for (int i = 0; i < Directions::NUM_DIRECTIONS; ++i)
	{
		const Vec2i adjacentTileDirection{ Directions::toVector(static_cast<Direction>(i)) };

		const Vec2i offset{ (adjacentTileDirection + tileCompOffset) / TileData::DIMENSION };

		const Vec2i adjacentTilesChunkPos{ this->getChunkPos(chunkPos, tilePos, offset) };
		const Vec2i adjacentTilesPos{ this->getTilePos(tilePos, offset) };

		// check adjacent tile components
		if (
			this->chunks.find(adjacentTilesChunkPos) != this->chunks.end() &&
			baseTileID == chunks.at(adjacentTilesChunkPos).getTile(adjacentTilesPos).getBase().id
			)
			direction = Directions::subtract(direction, static_cast<Direction>(i));
	}

	return direction;
}
