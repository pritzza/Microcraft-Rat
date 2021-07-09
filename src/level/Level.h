#pragma once

#include "World.h"

class Level
{
private:
	World world;

public:

	void generateWorld();

	inline const World& getWorld() const { return this->world; }
};