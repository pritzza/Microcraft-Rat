#include "Renderer.h"

#include "ColorPalette.h"

#include <limits>
#include <cassert>

#include <iostream>

Renderer::Renderer(const uint16_t width, const uint16_t height)
	:
	bufferWidth( width ),
	bufferHeight( height ),
	bufferSize( width * height )
{
	this->buffer.create(width, height, sf::Color(123,123,123));
	generateColorPalette();
}

void Renderer::render(const SpriteSheet& sheet, const SpriteSheet::SpriteID id, const ColorPalette& cp, const uint16_t x, const uint16_t y)
{
	const Sprite& s{ sheet.getSprite(id) };

	for (uint8_t ix = 0; ix < s.w; ++ix)
		for (uint8_t iy = 0; iy < s.h; ++iy)
		{
			this->putPixel(
				x + ix, 
				y + iy, 
				*(cp.getColors() + ( (sheet.getData()[s.w + ix + ((s.y + iy) * sheet.getWidth())] & 0b1100'0000) >> ix % 4) )
				// suprise, this doesnt work
			);
		}
}

void Renderer::generateColorPalette()
{
	const uint8_t min{ Color::getMinValue() };
	const uint8_t max{ Color::getMaxValue() };

	// iterate through every rgb value and put it in the master colorPalette
	for (int r = min; r <= max; ++r)
		for (int g = min; g <= max; ++g)
			for (int b = min; b <= max; ++b)
				this->colorPalette[paletteUsed++].setData(r, g, b);

	// for transparency, we will make the last pixel of the 
	this->colorPalette[TRANSPARENT_COLOR_INDEX].makeTransparent();
}

void Renderer::putPixel(const uint16_t i, const Color c)
{
	const uint16_t x = i % bufferWidth;
	const uint16_t y = i / bufferWidth;

	this->putPixel(x, y, c);
}

void Renderer::putPixel(const uint16_t x, const uint16_t y, const Color c)
{
	if (!c.isTransparent())
	{
		static constexpr uint8_t NORMAL_COLOR_MAX{ std::numeric_limits<uint8_t>::max() };

		// normalize each color channel from Color::MIN_VAL-Color::MAX_VAL to 0-255
		const uint8_t r = (c.getRed()	* NORMAL_COLOR_MAX) / Color::getColorRange();
		const uint8_t g = (c.getGreen() * NORMAL_COLOR_MAX) / Color::getColorRange();
		const uint8_t b = (c.getBlue()	* NORMAL_COLOR_MAX) / Color::getColorRange();

		// the renderer's buffer contains the pixel data that is going on the screen
		// so here is where we are actually telling which pixel goes on the screen
		this->buffer.setPixel(x, y, sf::Color{ r, g, b });
	}
}

void Renderer::testPalette()
{
	static uint8_t DISTORTION{ 0 };
	static constexpr bool DISTORT{ false };

	if (DISTORT)
	{
		if (DISTORTION >= PALETTE_SIZE)
			DISTORTION = 0;
		else
			DISTORTION++;
	}

	for (int i = 0; i < bufferSize; ++i)
	{
		this->putPixel(i, this->colorPalette[i % (PALETTE_SIZE - (i % (DISTORTION + 1)))]);
	}
}