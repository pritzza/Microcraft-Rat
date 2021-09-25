#pragma once

enum class RenderFlag
{
	NONE = 0b00,
	FLIP_X = 0b01,
	FLIP_Y = 0b10,
	FLIP_BOTH = FLIP_X | FLIP_Y
};