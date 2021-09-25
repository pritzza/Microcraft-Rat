#pragma once

#include "Chunk.h"

#include <unordered_map>

class WorldGenerator;

class Camera;
enum class Direction;

class World
{
private:
	WorldGenerator& worldGen;

	std::unordered_map<Vec2i, Chunk, Vec2iUtil> chunks;

	double time{};

private:
	void loadChunk(const Vec2i& pos);
	void unloadChunk(const Vec2i& pos);

	void loadSurroundingChunks(const Camera& camera, const int loadDistance);
	void unloadOutOfViewChunks(const Camera& camera, const int loadDistance);

	void updateTileDirections(const Vec2i& chunkCoord);

public:
	World(WorldGenerator& worldGen)
		:
		worldGen{ worldGen }
	{}

	void update(const double dt, const Camera& camera);

	const DetailedDirection getTileDirection(const Vec2i& chunkPos, const Vec2i& tilePos, const int tileSpriteIndex) const;

	const Vec2i getChunkPos(const Vec2i& chunkPos, const Vec2i& tilePos, const Vec2i& tileOffset) const;
	const Vec2i getTilePos(const Vec2i& tilePos, const Vec2i& tileOffset) const;
	const Vec2i getTileComponentPixelPos(const Vec2i& chunkCoord, const int tileIndex, const int tileComponentIndex) const;

	const auto getChunks() const { return this->chunks; }

	friend class WorldGenerator;
};