#include "WorldGenerator.h"

#include "../World.h"

#include "../../util/Vector.h"

#include <iostream>

void WorldGenerator::generateChunk(const Vec2i& chunkCoord, World& world)
{
	Chunk& chunk{ world.chunks.at(chunkCoord) };

	// between 0.1 and 64
	static constexpr double TERRAIN_FREQUENCY{ 8.f };
	static constexpr double FEATURE_FREQUENCY{ 3.f };

	const Vec2i chunkOffset{ chunkCoord * Chunk::getLength() };

	double terrainNoise;
	double featureNoise;
	double flavorNoise;

	for (int i = 0; i < Chunk::getSize(); ++i)
	{
		const Vec2i tileCoord{ Vec2i::toVector(i, Chunk::getLength(), Chunk::getLength()) };
		const Vec2i sample( tileCoord + chunkOffset );

		perlinNoise.reseed(this->terrainSeed);
		terrainNoise = perlinNoise.noise2D_0_1(sample.x / TERRAIN_FREQUENCY, sample.y / TERRAIN_FREQUENCY);

		Tile& tile{ chunk.getTile(tileCoord) };

		tile.setBase(genTileBase(terrainNoise));

		for (int j = 0; j < TileData::NUM_COMPONENTS; ++j)
			tile.getBase().randomNums[j] = terrainNoise * 69420;

		//tile.setFeature(genTileFeature(featureNoise));
	}
}

void WorldGenerator::generateTerrain(const Vec2i& chunkCoord, World& world)
{
}

void WorldGenerator::generateFeatures(const Vec2i& chunkCoord, World& world)
{
}

const TileBase::ID WorldGenerator::genTileBase(const float noiseValue)
{
	static constexpr double WATER_MAX{ 0.4 };
	static constexpr double GRASS_MAX{ 0.7 };
	static constexpr double STONE_MAX{ 1.0 };
	
	if		(noiseValue < WATER_MAX)	return TileBase::ID::Water;
	else if (noiseValue < GRASS_MAX)	return TileBase::ID::Grass;
	else if (noiseValue < STONE_MAX)	return TileBase::ID::Stone;
}

const bool WorldGenerator::isTileFeatureOnComponent()
{
	return true;
}