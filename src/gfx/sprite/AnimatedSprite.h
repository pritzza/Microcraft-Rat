#pragma once

#include "Sprite.h"

class AnimatedSprite : public Sprite
{
	enum class Animations
	{
		// already defined in dir class
		Left,
		Right,
		Up,
		Down,
		Num
	};
public:
	const float cycleLength;
	float curFrame;
};