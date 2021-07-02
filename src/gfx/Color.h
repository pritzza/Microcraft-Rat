#pragma once

#include "../util/Clamp.h"

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
	static constexpr uint8_t CHANNEL_BIT_DEPTH{ 4 };	// need to find a way to calculate this
	// you can represent the value 6 using 4 bits though

	static constexpr uint8_t BYTE{ 8 };	// should move this elsewhere, but 8 bits in a byte

	static constexpr uint8_t RED_OFFSET  { CHANNEL_BIT_DEPTH * 0 };
	static constexpr uint8_t GREEN_OFFSET{ CHANNEL_BIT_DEPTH * 1 };
	static constexpr uint8_t BLUE_OFFSET { CHANNEL_BIT_DEPTH * 2 };

	static constexpr uint16_t TRANSPARENT{ 0b1111'0000'0000'0000 };

private:
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
		value = clamp(value, MIN_VAL, MAX_VAL);

		// shift data so the 4 bit channel we want to edit are are the beginning
		// overwrite first 4 bits with 0s
		// insert the value into the first 4 bits of data
		// shift everything back
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

	inline const static uint8_t getColorRange() { return COLOR_RANGE; }
	inline const static uint8_t getMinValue()	{ return MIN_VAL;	  }
	inline const static uint8_t getMaxValue()	{ return MAX_VAL;     }
};