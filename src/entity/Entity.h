#pragma once

#include "../gfx/sprite/animation/AnimatedSprite.h"
#include "../gfx/color/ColorPalette.h"

#include "../util/Direction.h"

enum class AnimatedSpriteID;

class Entity
{
private:
	ColorPalette colorPalette;
	AnimatedSprite animatedSprite;

	Vec2i dim;

	int xPos, yPos, zPos;
	int xVel, yVel, zVel;

	float kbX, kbY, kbZ;

	int prevPosX, prevPosY, prevPosZ;
	int prevVelX, prevVelY, prevVelZ;

	int weight;

	bool isMoving{ false };
	bool isSubmerged{ false };

	Direction currentDirection{ Direction::South };
	Direction prevDirection{ Direction::South };

public:
	Entity(const AnimatedSpriteID animatedSpriteID, const ColorPalette colorPalette);

	void move(const Vec2i& vel);

	void update(const double dt);

	const Vec2i getCenterPos() const;

	const AnimatedSprite& getAnimatedSprite() const { return animatedSprite;		}
	const ColorPalette& getPalette() const			{ return colorPalette;			}
	const Direction getDirection() const			{ return currentDirection;		}
	const Vec2i getPos() const						{ return Vec2i{ xPos, yPos };	}

};