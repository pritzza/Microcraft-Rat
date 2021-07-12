#pragma once

#include "../../util/Binary.h"

#include <cstdint>

class Color
{
private:
	// min and max channel value for rgb
	static constexpr uint8_t MIN_VAL{ 0 };
	static constexpr uint8_t MAX_VAL{ 5 };

	// each color channel can have 6 different values
	// 6 x 6 x 6 = 216 possible colors
	static constexpr uint8_t COLOR_RANGE{ (MAX_VAL - MIN_VAL) + 1 };
	static constexpr uint8_t CHANNEL_BIT_DEPTH{ Binary::calculateBitDepth(COLOR_RANGE) + 1 };
	// + 1 because when designing this earlier i was using 4 bits and now im too lazy to chance
	// you can represent the value 6 using 3* bits though

	static constexpr uint8_t RED_OFFSET  { CHANNEL_BIT_DEPTH * 0 };
	static constexpr uint8_t GREEN_OFFSET{ CHANNEL_BIT_DEPTH * 1 };
	static constexpr uint8_t BLUE_OFFSET { CHANNEL_BIT_DEPTH * 2 };

	// arbitrary set of bits that represent transparency
	static constexpr uint16_t TRANSPARENT{ 0b1111'0000'0000'0000 };

private:
	// CORRECTION: you can actually use 3 bits per channel to
	// 	   repreesnt 6 different states, so imagine this but with
	// 	   3 bits per channel instead
	// 
	// we will store out color data in 16 bytes
	// bitmap for data will look something like this
	//		B    G	  R
	//      ____ ____ ____  
	// 0000 0000 0000 0000
	//
	// technically since we're giving 4 bytes per channel like that,
	// the channel depth could go up to 8 with no complications
	// we're wasting the 4 leading bytes though which is kinda dookie

	uint16_t data;

private:
	
	inline void setChannel(uint8_t value, const uint8_t offset) 
	{
		value = Math::clamp(value, MIN_VAL, MAX_VAL);

		// shift data so its bits are at the beginning		// so its easier to work with
		// overwrite the first 4 bits with 0s				// to clear any prev data
		// insert the value into the first 4 bits of data	// putting the new data in
		// shift everything back							// to restore bitset/map form
		data = (((data >> offset) & 0b1111'1111'1111'0000) | value) << offset;
	}

public:
	Color(const uint8_t r, const uint8_t g, const uint8_t b) { this->setData(r, g, b); }
	Color(const uint16_t data) : data{ data }				 {						   }
	Color()					   : data{ 0 }					 {						   }

	void makeTransparent();
	const bool isTransparent() const;

	void setData (const uint8_t r, const uint8_t g, const uint8_t b);
	inline void setData (const uint16_t data) { this->data = data;       }
	inline void setRed  (const uint8_t r) { setChannel(r, RED_OFFSET);   }
	inline void setGreen(const uint8_t g) { setChannel(g, GREEN_OFFSET); }
	inline void setBlue (const uint8_t b) { setChannel(b, BLUE_OFFSET);  }

	inline const uint16_t getData() const { return this->data; }
	inline const uint8_t getRed() const   { return (this->data >> RED_OFFSET)   & 0b0000'0000'0000'1111; }
	inline const uint8_t getGreen() const { return (this->data >> GREEN_OFFSET) & 0b0000'0000'0000'1111; }
	inline const uint8_t getBlue() const  { return (this->data >> BLUE_OFFSET)  & 0b0000'0000'0000'1111; }

	inline constexpr static uint8_t getColorRange() { return COLOR_RANGE; }
	inline constexpr static uint8_t getMinValue()	{ return MIN_VAL;	  }
	inline constexpr static uint8_t getMaxValue()	{ return MAX_VAL;     }
};