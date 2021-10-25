#pragma once

#include "World.h"
#include "generation/WorldGenerator.h"

class Camera;

class Level
{
private:
	WorldGenerator worldGenerator{ 0, 1, 2 };
	World world{ worldGenerator };
	
public:
	// TODO make constructor for different "types" of worlds, like surface, underground, etc

	void update(const double dt, const Camera& camera);

	const World& getWorld() const { return this->world; }
};