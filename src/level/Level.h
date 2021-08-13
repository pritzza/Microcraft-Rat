#pragma once

#include "World.h"

class Camera;

class Level
{
private:
	World world;

public:
	Level(const Vec2i windowDimensions);

	void update(const double dt, const Camera& camera);

	inline const World& getWorld() const { return this->world; }
};