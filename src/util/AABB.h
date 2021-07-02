#pragma once

#include <cstdint>

struct AABB
{
	uint8_t x, y, w, h;

	AABB()
		:
		x{ 0 },
		y{ 0 },
		w{ 8 },
		h{ 8 }
	{}

	AABB(const uint8_t x, const uint8_t y, const uint8_t w, const uint8_t h)
		:
		x{ x },
		y{ y },
		w{ w },
		h{ h }
	{}
};