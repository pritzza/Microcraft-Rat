#include "Level.h"

void Level::generateWorld()
{
	this->world.loadChunk( Vec2i{ 1, 1 } );
}