#include "Renderer.h"

#include <limits>
#include <cassert>

Renderer::Renderer(const uint16_t width, const uint16_t height)
	:
	bufferWidth( width ),
	bufferHeight( height ),
	bufferSize( width * height )
{
	generateColorPalette();
	this->buffer.create(width, height, sf::Color(123,123,123));
}

void Renderer::generateColorPalette()
{
	const uint8_t range{ Color::getColorRange() };

	int i{};
	for (int r = 1; r <= range; ++r)
		for (int g = 1; g <= range; ++g)
			for (int b = 1; b <= range; ++b)
			{
				this->colorPalette[i].setData(r, g, b);
				++i;
			}
}

void Renderer::putPixel(const uint16_t i, const Color c)
{
	const uint16_t x = i % bufferWidth;
	const uint16_t y = i / bufferWidth;

	this->putPixel(x, y, c);
}

void Renderer::putPixel(const uint8_t x, const uint8_t y, const Color c)
{
	// normalize each color channel from Color::MIN_VAL-Color::MAX_VAL to 0-255
	static constexpr uint8_t NORMAL_COLOR_MAX{ std::numeric_limits<uint8_t>::max() };

	const int r = (c.getRed()	* NORMAL_COLOR_MAX) / Color::getColorRange();
	const int g = (c.getGreen() * NORMAL_COLOR_MAX) / Color::getColorRange();
	const int b = (c.getBlue()	* NORMAL_COLOR_MAX) / Color::getColorRange();

	this->buffer.setPixel(x, y, sf::Color(r, b, g));
}

void Renderer::testPalette()
{
	constexpr static uint8_t DISTORTION{ 69 };
	assert(DISTORTION < Renderer::PALLET_SIZE && DISTORTION);	// must be non 0 and less than pallet size

	for (int i = 0; i < bufferSize; ++i)
		this->putPixel(i, this->colorPalette[i % (Renderer::PALLET_SIZE - (i % DISTORTION))]);
}