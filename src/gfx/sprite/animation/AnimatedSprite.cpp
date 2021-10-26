#include "AnimatedSprite.h"

#include "../../sheet/SpriteSheetAnimationData.h"

void AnimatedSprite::update(const double dt, const bool usingGlobalTimer)
{
	const double keyFrameDuration{ getSpriteData().frameDuration };
	const int numKeyFrames{ getFrameData().getNumFrames(currentDir) };

	// the global timer would be used by tiles to keep all tile animations in sync
	// the global timer is literally just the World's time
	if (usingGlobalTimer)
		currentFrame = static_cast<int>(dt / keyFrameDuration) % numKeyFrames;
	else
	{
		currentFrameProgress += dt;

		if (currentFrameProgress > keyFrameDuration)
		{
			currentFrame += currentFrameProgress / keyFrameDuration;

			if (currentFrame >= numKeyFrames)
				currentFrame -= numKeyFrames;

			currentFrameProgress -= static_cast<int>(currentFrameProgress / keyFrameDuration) * keyFrameDuration; // trunc
		}
	}
}

void AnimatedSprite::resetAnimation()
{
	currentFrame = 0;
	currentFrameProgress = 0;
}

void AnimatedSprite::setID(const AnimatedSpriteID asID)
{
	animatedSpriteID = asID;
	resetAnimation();
}

const RenderFlag AnimatedSprite::getRenderFlags() const
{
	const std::vector<KeyFrameData>& keyFrameData{ getFrameData().getAnimation(getDirection()) };

	return keyFrameData[currentFrame].transformation;
}

const bool AnimatedSprite::isAnimated() const
{
	return getSpriteData().frameDuration != 0.f;
}

const Vec2i AnimatedSprite::getDimensions() const
{
	return SpriteSheetData::getSpriteDimensions(getSpriteData().spriteID);
}

const int AnimatedSprite::getFrameIndex() const
{
	const std::vector<KeyFrameData>& keyFrameData{ getFrameData().getAnimation(currentDir) };

	return keyFrameData[currentFrame].index;
}

const AnimatedSpriteData& AnimatedSprite::getSpriteData() const
{
	return SpriteSheetAnimationData::getAnimatedSpriteData(animatedSpriteID);
}

const AnimationFrameData& AnimatedSprite::getFrameData() const
{
	const AnimatedSpriteData& spriteData{ getSpriteData() };

	return SpriteSheetAnimationData::getAnimationFrameData(spriteData.animationType);
}

const Vec2i AnimatedSprite::getAnimationBounds() const
{
	return SpriteSheetData::getSpriteSheetBounds(getSpriteData().spriteID);
}
