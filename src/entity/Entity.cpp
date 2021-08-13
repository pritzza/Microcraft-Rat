#include "Entity.h"

#include <iostream>

#include "../gfx/sprite/SpriteSheet.h"

Entity::Entity(const AnimatedSpriteData& animatedSpriteData)
	:
	animatedSprite{ animatedSpriteData },
	dim{ SpriteSheet::getSpriteDimensions(this->animatedSprite.getSpriteData().spriteID) },
	xPos{ 0 }, yPos{ 0 }, zPos{ 0 },
	xVel{ 0 }, yVel{ 0 }, zVel{ 0 }
{}

void Entity::move(const Vec2i& vel)
{
	this->xVel += vel.x;
	this->yVel += vel.y;

	if (xVel || yVel)
	{
		this->currentDirection = Directions::toDirection( Vec2i{ xVel, yVel } );
	}
}

void Entity::update(const double dt)
{
	if (xVel || yVel)
	{
		animatedSprite.update(dt);

		this->xPos += xVel;
		this->yPos += yVel;

		this->xVel = 0;
		this->yVel = 0;
	}
}

const Vec2i Entity::getCenterPos() const
{
	return Vec2i{ xPos, yPos } + (SpriteSheet::getSpriteDimensions(animatedSprite.getSpriteData().spriteID) / 2);
}
