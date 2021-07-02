#include "SpriteSheet.h"

#include <SFML/Graphics/Image.hpp>

#include <cassert>

#include <iostream>
#include <bitset>

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
		assert(spriteSheetBuffer.getSize().x == SHEET_WIDTH);
		assert(spriteSheetBuffer.getSize().y == SHEET_HEIGHT);

		uint8_t imagePixel;

		static constexpr uint8_t NUM_CHANNELS{ 4 };

		// iterate by 4 since here we'll only care about the value of one color channel
		// that being R, and not G, B, or A
		for (int i = 0; i < SHEET_SIZE / NUM_CHANNELS; ++i)
		{
			imagePixel = *(spriteSheetBuffer.getPixelsPtr() + (i * NUM_CHANNELS));	// could prolly optimize with i << 2

			// we only care about the two leading bits
			static constexpr uint8_t DETERMINING_BITS{ 0b1100'0000 };
			const uint8_t shift = PIXEL_BIT_DEPTH * (i % PIXELS_PER_BYTE);

			this->data[i/PIXELS_PER_BYTE] |= ((imagePixel & DETERMINING_BITS) >> shift);
		}
	}
}

const Sprite& SpriteSheet::getSprite(const SpriteSheet::SpriteID s) const
{
	return this->SPRITES[static_cast<uint8_t>(s)];
}