#pragma once

#include "Vector.h"
#include "Math.h"

enum class DetailedDirection
{
	NorthWest,	// 0
	North,		// 1
	NorthEast,	// 2
	West,		// 3
	Center,		// 4
	East,		// 5
	SouthWest,	// 6
	South,		// 7
	SouthEast	// 8
};

enum class Direction
{
	North = 0,
	South = 1,
	East  = 2,
	West  = 3,

	Up	  = 0,
	Down  = 1,
	Right = 2,
	Left  = 3
};

class Directions
{
public:
	static constexpr int NUM_DIRECTIONS{ 4 };
	static constexpr int SQRT_NUM_DIRS{ 2 };

	static constexpr int NUM_DET_DIRECTIONS{ 9 };
	static constexpr int SQRT_NUM_DET_DIRS{ 3 };

public:
	static constexpr Vec2i toVector(const Direction dir)
	{
		switch (static_cast<int>(dir))
		{
		case 0: return Vec2i{  0, -1 };		// Up/North
		case 1: return Vec2i{  0,  1 };		// Down/South
		case 2: return Vec2i{  1,  0 };		// Right/East
		case 3: return Vec2i{ -1,  0 };		// Left/West
		}
	}

	static constexpr Vec2i toVector(const DetailedDirection dir)
	{
		switch (dir)
		{
		case DetailedDirection::NorthWest:	return { -1, -1 };
		case DetailedDirection::North:		return {  0, -1 };
		case DetailedDirection::NorthEast:	return {  1, -1 };
		case DetailedDirection::East:		return {  1,  0 };
		case DetailedDirection::Center:		return {  0,  0 };
		case DetailedDirection::West:		return { -1,  0 };
		case DetailedDirection::SouthWest:	return { -1,  1 };
		case DetailedDirection::South:		return {  0,  1 };
		case DetailedDirection::SouthEast:	return {  1,  1 };
		}
	}

	static constexpr DetailedDirection toDetailedDirection(const Vec2i vec)
	{
		const Vec2i cleanedVec{ Math::clamp(vec.x, -1, 1), Math::clamp(vec.y, -1, 1) };

		return static_cast<DetailedDirection>(Vec2i::toIndex(cleanedVec + 1, SQRT_NUM_DET_DIRS, SQRT_NUM_DET_DIRS));
	}

	static constexpr Direction opposite(const Direction d)
	{
		// could make algo, but whatever
		switch (d)
		{
		case Direction::North: return Direction::South;
		case Direction::South: return Direction::North;
		case Direction::East:  return Direction::West;
		case Direction::West:  return Direction::East;
		}
	}

	static constexpr DetailedDirection opposite(const DetailedDirection d)
	{
		return subtract(DetailedDirection::Center, d);
	}
	
	static constexpr Direction toDirection(const Vec2i vec)
	{
		Vec2i cleanedVec{ Math::clamp(vec.x, -1, 1), Math::clamp(vec.y, -1, 1) };
	
		if (cleanedVec.x == -1)
			return Direction::Left;
		if (cleanedVec.x == 1)
			return Direction::Right;
		if (cleanedVec.y == -1)
			return Direction::Up;
		if (cleanedVec.y == 1)
			return Direction::Down;

		//if (cleanedVec.x && cleanedVec.y)
		//	cleanedVec.y = 0;
		//
		//const Direction dir{ static_cast<Direction>(Vec2i::toIndex(cleanedVec, SQRT_NUM_DIRS, SQRT_NUM_DIRS)) };

		//return dir;
	}
	
	static constexpr Direction add(const Direction addor, const Direction addend)
	{
		const Vec2i addorVec{ toVector(addor) };
		const Vec2i addendVec{ toVector(addend) };
	
		return toDirection(addorVec + addendVec);
	}

	static constexpr DetailedDirection add(const DetailedDirection addor, const Direction addend)
	{
		const Vec2i addorVec{ toVector(addor) };
		const Vec2i addendVec{ toVector(addend) };
		const DetailedDirection finalDirection{ toDetailedDirection(addorVec + addendVec) };
		return finalDirection;
	}

	static constexpr DetailedDirection add(const DetailedDirection addor, const DetailedDirection addend)
	{
		const Vec2i addorVec{ toVector(addor) };
		const Vec2i addendVec{ toVector(addend) };
		const DetailedDirection finalDirection{ toDetailedDirection(addorVec + addendVec) };
		return finalDirection;
	}

	static constexpr DetailedDirection subtract(const DetailedDirection addor, const Direction addend)
	{
		const Vec2i addorVec{ toVector(addor) };
		const Vec2i addendVec{ toVector(addend) };
		const DetailedDirection finalDirection{ toDetailedDirection(addorVec - addendVec) };
		return finalDirection;
	}

	static constexpr DetailedDirection subtract(const DetailedDirection addor, const DetailedDirection addend)
	{
		const Vec2i addorVec{ toVector(addor) };
		const Vec2i addendVec{ toVector(addend) };
		const DetailedDirection finalDirection{ toDetailedDirection(addorVec - addendVec) };
		return finalDirection;
	}
};