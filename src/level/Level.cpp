#include "Level.h"

void Level::generateWorld()
{
	this->world.loadChunk( Vec2i{ 0, 0 } );
}