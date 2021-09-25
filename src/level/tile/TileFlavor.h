#pragma once

// a flavor is an data type that represents an alternate look for a tile's base or feature
// ngl this class is kinda stupid and i might just delete it
struct TileFlavor
{
public:
	static constexpr int DIMENSION{ 2 };
	static constexpr int NUM_FLAVORS{ DIMENSION * DIMENSION };

	static constexpr int NO_FLAVOR{ 0 };

private:
	int value;
	bool hasFlavor;

public:
	TileFlavor(const int value = NO_FLAVOR, const bool hasFlavor = false)
		:
		value{ value % NUM_FLAVORS },
		hasFlavor{ hasFlavor }
	{}

	constexpr void setValue(const int v)
	{
		value = v % NUM_FLAVORS;
	}

	constexpr int getValue() const
	{	
		if (hasFlavor)
			return value;
		else
			return NO_FLAVOR;
	}

	constexpr void setFlavor(const bool f)
	{
		hasFlavor = f;
	}

	constexpr bool isFlavored() const
	{
		return hasFlavor;
	}
};