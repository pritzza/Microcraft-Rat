#include "World.h"

void World::loadChunk(const Vec2i& pos)
{
	// probably pass the seed into the chunk later when doing world gen
	this->chunks.insert(std::pair{ pos, Chunk{} });
}

void World::unloadChunk(const Vec2i& pos)
{
}