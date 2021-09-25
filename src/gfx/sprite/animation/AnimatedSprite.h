#pragma once

#include "AnimatedSpriteData.h"
#include "AnimationFrameData.h"

#include "../../../util/Direction.h"

struct AnimationData;
enum class AnimatedSpriteID;

enum class RenderFlag;

struct Vec2i;

struct AnimatedSprite
{
private:
	AnimatedSpriteID spriteID;

	Direction currentDir{ Directions::DEFAULT_DIR };

	int currentFrame{};

	double currentFrameProgress{ 0.f };

public:
	AnimatedSprite(const AnimatedSpriteID spriteID)
		:
		spriteID{ spriteID }
	{}

	void update(const double dt, const bool usingUniversalTimer = false);

	void resetAnimation();

	void setID(const AnimatedSpriteID asID);
	void setDirection(const Direction dir)			{ currentDir = dir;		}

	const RenderFlag getRenderFlags() const;

	const bool isAnimated() const;
	const Vec2i getDimensions() const;
	const int getFrameIndex() const;
	const AnimatedSpriteData& getSpriteData() const;
	const AnimationFrameData& getFrameData() const;

	const int getCurrentFrame() const				{ return currentFrame;	}
	const Direction getDirection() const			{ return currentDir;	}
};