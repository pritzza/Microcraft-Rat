#pragma once

#include "Math.h"

#include <cstdint>

class Binary
{
public:
	static constexpr uint8_t BYTE{ 8 };

public:
	// calculates how many bits it takes to store n different states
	template<typename T>
	inline static constexpr int calculateBitDepth(T checking, const unsigned int i = 1)
	{
		if (Math::ipow(2, i) < checking)
			return calculateBitDepth(checking, i + 1);
		else
			return i;
	}
};