#include "WorldGenerator.h"

#include "../World.h"

#include "../../util/Vector.h"

void WorldGenerator::generateChunk(const Vec2i& chunkCoord, World& world)
{
	Chunk& chunk{ world.chunks.at(chunkCoord) };

	// between 0.1 and 64
	static constexpr double FREQUENCY{ 8.f };

	const Vec2i tileOffset{ chunkCoord * Chunk::getLength() };

	double noiseValue;

	for (int y = 0; y < Chunk::getLength(); ++y)
		for (int x = 0; x < Chunk::getLength(); ++x)
		{
			const Vec2i tileCoord{ x, y };

			Tile& tile{ chunk.getTile(tileCoord) };

			noiseValue = perlinNoise.noise2D_0_1((x + tileOffset.x) / FREQUENCY, (y + tileOffset.y) / FREQUENCY);

			generateTileTerrain(tile, noiseValue);
		}
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

const TileFeature::ID WorldGenerator::genTileFeature()
{
	static constexpr int FLOWER	{ 10 };
	static constexpr int TREE	{ 10 };

	static constexpr int NUM_FEATURES{ static_cast<int>(TileFeature::ID::NumFeatures) };

	if (rng.getNum(0, 100) < FLOWER)
		return TileFeature::ID::Flower;

	if (rng.getNum(0, 100) < TREE)
		return TileFeature::ID::Tree;
}

const bool WorldGenerator::isTileFeatureOnComponent()
{
	static constexpr int FLOWER	{ 50 };

	return rng.getNum(0, 100) < FLOWER;
}

void WorldGenerator::generateTileTerrain(Tile& tile, const float noiseValue)
{
	tile.setBase(genTileBase(noiseValue));

	for (int i = 0; i < TileData::NUM_COMPONENTS; ++i)
	{
		// TODO redo all terrain gen
		// tile base component flavor generation

		const bool isTileBaseFlavored = rng.getNum(0, 2);

		if (isTileBaseFlavored)
		{
			tile.getBase().flavors[i].setFlavor(true);

			const int tileBaseFlavorValue{ rng.getNum(0, TileFlavor::NUM_FLAVORS) };
			tile.getBase().flavors[i].setValue(tileBaseFlavorValue);
		}

		// tile feature component flavor generation

		const bool isTileFeatureFlavored = rng.getNum(4, 5);

		if (isTileFeatureFlavored)
		{
			tile.getFeature().flavors[i].setFlavor(true);

			const int tileFeatureFlavorValue{ rng.getNum(0, TileFlavor::NUM_FLAVORS) };
			tile.getFeature().flavors[i].setValue(tileFeatureFlavorValue);
		}

		if (tile.getBase().id == TileBase::ID::Grass)
		{
			// try to spawn flower
			if (rng.getNum(0, 8) == 0)
			{
				tile.setFeature(TileFeature::ID::Flower);
				tile.getFeature().isOnComponent[i] = true;
			}

			// try to spawn tree
			if (rng.getNum(0, 8) == 0)
			{
				tile.setFeature(TileFeature::ID::Tree);
				tile.getFeature().isOnComponent[0] = true;
			}
		}
	}
}