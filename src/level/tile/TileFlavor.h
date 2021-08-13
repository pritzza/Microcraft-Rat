#pragma once

// a flavor is an data type that represents an alternate look for a tile's base or feature
struct TileFlavor
{
public:
	static constexpr int DIMENSION{ 2 };
	static constexpr int NUM_FLAVORS{ (DIMENSION * DIMENSION) + 1 };

	static constexpr int NO_FLAVOR{ 0 };

private:
	int value{ NO_FLAVOR };

public:

	inline constexpr void disableFlavor()
	{
		this->value = NO_FLAVOR;
	}

	inline constexpr void setValue(const int v)
	{
		if (v < NO_FLAVOR)
			this->value = NO_FLAVOR;
		else
			this->value = v % NUM_FLAVORS;
	}

	inline constexpr int getValue() const
	{	
		return this->value;
	}

	inline constexpr bool hasFlavor() const
	{
		return this->value != NO_FLAVOR;
	}

	inline constexpr int operator+(TileFlavor other) const
	{
		other.setValue(value + other.getValue());

		return other.getValue();
	}

};