#pragma once

#include <unordered_map>

#include "Chunk.h"

#include "../util/Random.h"
#include "../util/Direction.h"
#include "../util/PerlinNoise.hpp"

class Camera;

class World
{
private:
	std::unordered_map<Vec2i, Chunk, Vec2iUtil> chunks;
	Random rng;

	siv::PerlinNoise perlinNoise;

	int terrainSeed;		// seed responsible for the terrain generation
	int tileFlavoringSeed;	// seed responsible for the flavors of tiles

private:
	void generateChunk(const Vec2i& pos);

public:
	World(const int terrainSeed, const int tileSeed);

	void update(const Camera& camera);

	void loadChunk(const Vec2i& pos);
	void unloadChunk(const Vec2i& pos);

	const DetailedDirection getTileDirection(const Vec2i& chunkPos, const Vec2i& tilePos, const int tileSpriteIndex) const;

	const Vec2i getChunkPos(const Vec2i& chunkPos, const Vec2i& tilePos, const Vec2i& tileOffset) const;
	const Vec2i getTilePos(const Vec2i& tilePos, const Vec2i& tileOffset) const;

	inline const auto getChunks() const { return this->chunks; }
};