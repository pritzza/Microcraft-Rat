#pragma once

#include "../gfx/sprite/AnimatedSprite.h"

#include "../util/Direction.h"

class Entity
{
private:
	AnimatedSprite animatedSprite;

	Vec2i dim;

	int xPos, yPos, zPos;
	int xVel, yVel, zVel;

	bool isMoving{ false };
	bool isSubmerged{ false };

	Direction currentDirection{ Direction::South };

public:
	Entity(const AnimatedSpriteData& animatedSpriteData);

	void move(const Vec2i& vel);

	void update(const double dt);

	const AnimatedSprite& getAnimatedSprite() const
	{
		return this->animatedSprite;
	}

	const Vec2i getPos() const
	{
		return Vec2i{ xPos, yPos };
	}

	const Vec2i getCenterPos() const;

	const Direction getDirection() const
	{
		return this->currentDirection;
	}
};