#pragma once

#include <unordered_map>

#include "Chunk.h"

#include "../util//Random.h"
#include "../util/Vector.h"

class Renderer;

class World
{
private:
	std::unordered_map<Vec2i, Chunk, Vec2iUtil> chunks;
	Random rng;

	int terrainSeed;		// seed responsible for the terrain generation
	int tileFlavoringSeed;	// seed responsible for the flavors of tiles

public:
	void loadChunk(const Vec2i& pos);
	void unloadChunk(const Vec2i& pos);

	inline const auto getChunks() const { return this->chunks; }
};