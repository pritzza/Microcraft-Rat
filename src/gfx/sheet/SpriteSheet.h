#pragma once

#include "../../util/Binary.h"
#include "../../util/Vector.h"

// there is one sprite sheet that will always be stored during runtime
// it will store all the sprite data for every sprite
// sprites will be colored at runtime, so they're store in grayscale here
class SpriteSheet
{
private:
	// because a uint8_t is 8 bits, and we only need 2 bits to store one pixel
	// we can store 4 pixels in one uint8_t, so there are 4 pixels per element
	static constexpr uint8_t PIXEL_BIT_DEPTH{ 2 };	// takes 2 bits to store 1 pixel

	static constexpr uint8_t PIXELS_PER_BYTE{ sizeof(uint8_t) * Binary::BYTE / PIXEL_BIT_DEPTH };	// we store data for 4 pixels every 1 uint8_t

	// we only care about the two leading bits
	// only used in sprite rendering and parsing spritesheet file
	static constexpr uint8_t DETERMINING_BITS{ 0b1100'0000 };

	static constexpr uint16_t SHEET_HEIGHT{ 256 };	// sprite sheet is 256x256 px (square)
	static constexpr uint16_t SHEET_WIDTH{ SHEET_HEIGHT / PIXELS_PER_BYTE };
	static constexpr uint16_t SHEET_SIZE{ SHEET_WIDTH * SHEET_HEIGHT };

private:
	uint8_t data[SHEET_WIDTH * SHEET_HEIGHT];

private:
	void loadFromFile(const std::string& fileName);

public:
	SpriteSheet(const std::string& fileName)
		:
		data{}
	{
		this->loadFromFile(fileName);
	}

	// returns 2 bit pixel at index of xy coord
	const uint8_t getPixel(const uint16_t x, const uint16_t y, const uint8_t i) const
	{
		const int index{ x + (y * SHEET_WIDTH) };
		return (this->data[index] & (DETERMINING_BITS >> (i * PIXEL_BIT_DEPTH))) >> (((PIXELS_PER_BYTE - 1) - i) * PIXEL_BIT_DEPTH);
	}

	const uint8_t* const getData() const				{ return this->data;		}

	static constexpr uint16_t getHeight()				{ return SHEET_HEIGHT;		}
	static constexpr uint16_t getWidth()				{ return SHEET_WIDTH;		}
	static constexpr uint8_t getPixelsPerByte()			{ return PIXELS_PER_BYTE;	}

};