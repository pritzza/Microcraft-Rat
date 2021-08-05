#include "SpriteSheet.h"

#include <SFML/Graphics/Image.hpp>

#include <cassert>

#include <iostream>

// this just in, ! is only the logical not operator
// ~ is the bitwise not operator... thank god i decided not
// to use a not operator otherwise i would've gotten an unexpected output
// and would have never suspected this...

SpriteSheet::SpriteSheet(const std::string& fileName)
	:
	data{}
{
	this->loadFromFile(fileName);
}

void SpriteSheet::loadFromFile(const std::string& fileName)
{
	sf::Image spriteSheetBuffer;

	if (!spriteSheetBuffer.loadFromFile(fileName))
		std::cerr << "Could't open spritesheet: " << fileName << '\n';
	else
	{
		assert(spriteSheetBuffer.getSize().x / PIXELS_PER_BYTE == SHEET_WIDTH);
		assert(spriteSheetBuffer.getSize().y == SHEET_HEIGHT);

		uint8_t imagePixel;

		static constexpr uint8_t NUM_CHANNELS{ 4 };

		// iterate by 4 since here we'll only care about the value of one color channel
		// that being R, and not G, B, or A
		for (int i = 0; i < SHEET_SIZE * PIXELS_PER_BYTE; ++i)
		{
			imagePixel = *(spriteSheetBuffer.getPixelsPtr() + (i * NUM_CHANNELS));	// could prolly optimize with i << 2

			const uint8_t shift = PIXEL_BIT_DEPTH * (i % PIXELS_PER_BYTE);

			this->data[i / PIXELS_PER_BYTE] |= ((imagePixel & DETERMINING_BITS) >> shift);
		}
	}
}