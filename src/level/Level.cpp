#include "Level.h"

#include "../gfx/Camera.h"

void Level::update(const double dt, const Camera& camera)
{
	world.update(dt, camera);
}
