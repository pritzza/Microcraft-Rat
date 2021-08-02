#pragma once

#include "../gfx/sprite/SpriteSheet.h"

class Entity
{
private:
	SpriteSheet::SpriteID spriteID;

	int xPos, yPos, zPos;
	int xVel, yVel, zVel;

	bool isMoving{false};
	bool isSubmerged{ false };

};