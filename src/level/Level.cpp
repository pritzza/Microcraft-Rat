#include "Level.h"

#include "../gfx/Camera.h"

Level::Level(const Vec2i windowDimensions)
	:
	world{0,0}
{}

void Level::update(const Camera& camera)
{
	this->world.update(camera);
}
