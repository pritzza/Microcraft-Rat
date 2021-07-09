#pragma once

#include "AABB.h"

struct Vec2i
{
	int x, y;

	bool operator==(const Vec2i& a) const {
		return a.x == x && a.y == y;
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
			return Vec2i{ index % w, index / w };	// x

		return Vec2i{ 0, 0 };
	}
};

// thanks ./README/RedLightning for helping me figure this out with the World::chunks unordered_map
struct Vec2iUtil {

	size_t operator() (const Vec2i& k) const {
		return std::hash<int>()(k.x) ^ (2 * std::hash<int>()(k.y));
	}
};

class Vec2iHash {
public:

	// Use sum of lengths of first and last names
	// as hash function.
	std::size_t operator()(const Vec2i& k) const
	{
		std::size_t h1 = std::hash<int>()(k.x);
		std::size_t h2 = std::hash<int>()(k.y);

		return h1 ^ h2;
	}
};
/*
struct Vec2i : public Vec2<int>
{
	Vec2i(const int x, const int y) : Vec2{ x, y } {}

	static inline constexpr int toIndex(const Vec2i& pos, const Vec2i& dim)
	{
		if (AABB::isPointInside(pos.x, pos.y, 0, 0, dim.w, dim.h))
			return pos.x + (pos.y * dim.w);

		return 0;
	}

	static inline const Vec2i toVector(const int index, const Vec2i& dim)
	{
		const Vec2i pos{ index % dim.x, index / dim.x };
		if (AABB::isPointInside(pos.x, pos.y, 0, 0, dim.x, dim.y))
			return pos;

		return { 0,0 };
	}
};

struct Vec2f : public Vec2<float>
{
	Vec2f(const int x, const int y) : Vec2{ x, y } {}
};

template<typename T>
struct Vec2
{
	T x, y;
	T& w{ x }, h{ y };

	// operator overloads
	Vec2& operator+=(const Vec2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}
	Vec2& operator*=(const T factor)
	{
		this->x *= factor;
		this->y *= factor;
		return *this;
	}
	Vec2& operator/=(const T factor)
	{
		this->x /= factor;
		this->y /= factor;
		return *this;
	}
	Vec2& operator+=(const T factor)
	{
		this->x += factor;
		this->y += factor;
		return *this;
	}
	Vec2& operator-=(const T factor)
	{
		this->x -= factor;
		this->y -= factor;
		return *this;
	}
};
*/