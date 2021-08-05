#pragma once

// a flavor is an data type that represents an alternate look for a tile's base or feature
struct TileFlavor
{
public:
	static constexpr int DIMENSION{ 2 };
	static constexpr int NUM_FLAVORS{ (DIMENSION * DIMENSION) + 1 };

public:
	enum class Value
	{
		None,
		One,
		Two,
		Three,
		Four
	};

	inline static constexpr int toIndex(const Value v)
	{
		// in terms of index, Value::None and Value::One should be the same
		return static_cast<int>(v) - (static_cast<int>(v) > static_cast<int>(Value::None));
	}
};