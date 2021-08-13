#include "AnimatedSprite.h"

#include "SpriteSheet.h"

#include "../Renderer.h"

const Vec2i AnimatedSprite::getStandardFrameCrop(const Direction dir) const
{
	static constexpr auto& isFrameLooping{ SpriteSheet::isStandardAnimationFrameLooping };

	const int dirIndex= SpriteSheet::getStandardAnimationDirectionIndex(dir);
	const int frameOffset = isTransformed * (!isFrameLooping(dirIndex));

	const Vec2i totalOffset{ dirIndex + frameOffset, 0 };

	return totalOffset;
}

const Vec2i AnimatedSprite::getMonoFrameCrop(const Direction dir) const
{
	return Vec2i{ 0, 0 };
}

const Vec2i AnimatedSprite::getTileFrameCrop() const
{
	return Vec2i{ 0, 0 };
}

void AnimatedSprite::update(const double dt)
{
	this->currentFrame += dt;

	if (currentFrame > data.frameDuration)
	{
		currentFrame -= data.frameDuration;
		
		isTransformed = !isTransformed;
	}
}

Vec2i AnimatedSprite::getFrameCrop(const Direction dir) const
{
	switch (this->data.animationType)
	{
	case AnimationType::Standard:
		return getStandardFrameCrop(dir);

	case AnimationType::Mono:
		return getMonoFrameCrop(dir);

	case AnimationType::Tile:
		return getTileFrameCrop();
	}
}

const RenderFlag& AnimatedSprite::getRenderFlags(const Direction dir) const
{
	const int dirIndex{ SpriteSheet::getStandardAnimationDirectionIndex(dir) };
	const bool flipX{ SpriteSheet::getStandardAnimationOrientation(dir, dirIndex) };
	const bool repeats{ SpriteSheet::isStandardAnimationFrameLooping(dirIndex) };

	// i have no idea how this works
	if ((repeats && this->isTransformed) || !flipX)
		return RenderFlag::FLIP_X;
	else
		return RenderFlag::NONE;
}
