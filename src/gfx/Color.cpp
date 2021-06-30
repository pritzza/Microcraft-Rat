#include "Color.h"

#include "../util/Clamp.h"

void Color::setData(uint8_t r, uint8_t g, uint8_t b)
{
	r = clamp(r, MIN_VAL, MAX_VAL);
	g = clamp(g, MIN_VAL, MAX_VAL);
	b = clamp(b, MIN_VAL, MAX_VAL);

	data = (r << RED_OFFSET) | (g << GREEN_OFFSET) | (b << BLUE_OFFSET);
}

void Color::setRed(uint8_t r)
{
	// clean up r
	r = clamp(r, MIN_VAL, MAX_VAL);

	// shift to right position
	//r = (r << RED_OFFSET);	// this step we cant actually do here
	// otherwise we get an arithmetic overflow, so we need to do it when
	// we're combining data and r with the bitwise or operator |

	// turn off all of the first 4 bits
	data = data & (!0b0000'0000'0000'1111);

	// add bits in r to data (or just add)
	// 0b0000'0011'0101'0000
	// 0b0000'0000'0000'0100
	//+=====================
	// 0b0000'0011'0101'0100

	data = data | (r << RED_OFFSET);
}

void Color::setGreen(uint8_t g)
{
	// clean up g
	g = clamp(g, MIN_VAL, MAX_VAL);

	// turn off all of the second 4 bits (the green bits)
	data &= !0b0000'0000'1111'0000;

	data = data | (g << GREEN_OFFSET);
}

void Color::setBlue(uint8_t b)
{
	// clean up b
	b = clamp(b, MIN_VAL, MAX_VAL);

	// turn off all of the third 4 bits (the blue bits)
	data &= !0b0000'1111'0000'0000;

	data = data | (b << GREEN_OFFSET);
}

const uint8_t Color::getRed() const
{
	return (this->data >> RED_OFFSET) & 0b0000'0000'0000'1111;;

}

const uint8_t Color::getGreen() const
{
	return (this->data >> GREEN_OFFSET) & 0b0000'0000'0000'1111;;

}

const uint8_t Color::getBlue() const
{
	return (this->data >> BLUE_OFFSET) & 0b0000'0000'0000'1111;;
}