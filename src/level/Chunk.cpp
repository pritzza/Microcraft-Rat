#include "Chunk.h"

#include "../util/Random.h"

#include "../util/Vector.h"

Chunk::Chunk(const int seed)
{
	//Random rng{seed};
	//
	//static constexpr int NUM_TILES{ static_cast<int>(Tiles::TileID::NumTiles) };
	//
	//// default initialize tileData to grass so we never have any nullptr nonsense
	//for (int i = 0; i < this->SIZE; ++i)
	//{
	//	this->setTile(i, static_cast<Tiles::TileID>( rng.getNum(0, NUM_TILES - 1) ));
	//}
}