#pragma once

#include "../../util/Random.h"
#include "../../util/PerlinNoise.hpp"

#include "../tile/Tile.h"

class World;
struct Chunk;
struct Vec2i;

class WorldGenerator
{
private:
	siv::PerlinNoise perlinNoise;

	const int terrainSeed;			// seed responsible for the terrain generation
	const int featureSeed;		// tile features...
	const int flavorSeed;	// seed responsible for the flavors of tiles

private:
	void generateTerrain(const Vec2i& chunkCoord, World& world);
	void generateFeatures(const Vec2i& chunkCoord, World& world);

	const TileBase::ID    genTileBase(const float noiseValue);
	//const TileFeature::ID genTileFeature(const float noiseValue);
	const bool isTileFeatureOnComponent();

public:
	WorldGenerator(const int terrainSeed, const int featureSeed, const int flavorSeed)
		:
		terrainSeed{ terrainSeed },
		featureSeed{ featureSeed },
		flavorSeed{ flavorSeed }
	{}

	void generateChunk(const Vec2i& chunkCoord, World& world);
};