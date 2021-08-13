#pragma once

#include "AnimatedSpriteData.h"

#include "../../util/Vector.h"
#include "../../util/Direction.h"

enum class RenderFlag;

class AnimatedSprite
{
private:
	const AnimatedSpriteData data;

	double currentFrame{ 0.f };
	bool isTransformed{ false };	// only 2 animation states per direction

private:
	const Vec2i getStandardFrameCrop(const Direction dir) const;
	const Vec2i getMonoFrameCrop(const Direction dir) const;
	const Vec2i getTileFrameCrop() const;

public:
	AnimatedSprite(const AnimatedSpriteData& data)
		:
		data{ data }
	{}

	void update(const double dt);

	Vec2i getFrameCrop(const Direction dir) const;

	const AnimatedSpriteData& getSpriteData() const
	{
		return data;
	}

	const RenderFlag& getRenderFlags(const Direction dir) const;
};