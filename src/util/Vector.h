#pragma once

#include "AABB.h"

#include <functional>

struct Vec2i
{
	int x, y;

	constexpr Vec2i(const int x, const int y)
		:
		x{ x },
		y{ y }
	{}

	constexpr Vec2i(const Vec2i& other)
		:
		x{ other.x },
		y{ other.y }
	{}

	void print() const;

	// operator overloads
	constexpr bool operator==(const Vec2i& a) const {
		return a.x == x && a.y == y;
	}

	constexpr void operator%=(const int modulator)
	{
		this->x %= modulator;
		this->y %= modulator;
	}

	constexpr void operator+=(const Vec2i& other)
	{
		this->x += other.x;
		this->y += other.y;
	}

	constexpr Vec2i operator+(const Vec2i& other) const	{ return Vec2i{ x + other.x,	 y + other.y	}; }
	constexpr Vec2i operator-(const Vec2i& other) const	{ return Vec2i{ x - other.x,	 y - other.y	}; }

	constexpr Vec2i operator*(const int multiplier) const { return Vec2i{ x * multiplier,  y * multiplier }; }
	constexpr Vec2i operator/(const int divisor) const	{ return Vec2i{ x / divisor,	 y / divisor	}; }
	constexpr Vec2i operator+(const int addend) const		{ return Vec2i{ x + addend,		 y + addend		}; }
	constexpr Vec2i operator-(const int subtractor) const { return Vec2i{ x - subtractor,  y - subtractor }; }

	// static functions
	static inline constexpr int toIndex(const Vec2i& vec, const int w, const int h)
	{
		if (AABB::isPointInside(vec.x, vec.y, 0, 0, w, h))
			return vec.x + (vec.y * w);

		return 0;
	}

	static inline constexpr int toIndex(const int x, const int y, const int w, const int h)
	{
		if (AABB::isPointInside(x, y, 0, 0, w, h))
			return x + (y * w);

		return 0;
	}

	static inline constexpr Vec2i toVector(const int index, const int w, const int h)
	{
		if (AABB::isPointInside(index % w, index / w, 0, 0, w, h))
			return Vec2i{ index % w, index / w };	// x, y

		return Vec2i{ 0, 0 };
	}
};

// thanks ./README/RedLightning for helping me figure this out with the World::chunks unordered_map
struct Vec2iUtil
{
	std::size_t operator() (const Vec2i& k) const
	{
		return std::hash<int>()(k.x) ^ (2 * std::hash<int>()(k.y));
	}
};