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
	Random rng;

	siv::PerlinNoise perlinNoise;

	const int terrainSeed;			// seed responsible for the terrain generation
	const int tileFeatureSeed;		// tile features...
	const int tileFlavoringSeed;	// seed responsible for the flavors of tiles

private:
	//void generateTerrain(World& world);
	//void generateFeatures(World& world);

	const TileBase::ID    genTileBase(const float noiseValue);
	const TileFeature::ID genTileFeature();
	const bool isTileFeatureOnComponent();

	void generateTileTerrain(Tile& tile, const float noiseValue);

public:
	WorldGenerator(const int terrainSeed, const int tileFeatureSeed, const int tileFlavoringSeed)
		:
		terrainSeed{ terrainSeed },
		tileFeatureSeed{ tileFeatureSeed },
		tileFlavoringSeed{ tileFlavoringSeed }
	{}

	void generateChunk(const Vec2i& chunkCoord, World& world);
};