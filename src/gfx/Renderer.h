#pragma once

#include <SFML/Graphics/Image.hpp>

#include <array>
#include <cstdint>
#include <limits>

#include "Color.h"

class Renderer
{
private:
	static constexpr uint16_t PALLET_SIZE{ 256 };
	
private:
	sf::Image buffer;

	const uint16_t bufferWidth;
	const uint16_t bufferHeight;
	const uint16_t bufferSize;

	std::array<Color, PALLET_SIZE> colorPalette;

private:
	void generateColorPalette();	// 6 for loops for each color channel

public:
	Renderer(const uint16_t width, const uint16_t height);

	// put a pixel on the image buffer
	void putPixel(const uint16_t i, const Color c);
	void putPixel(const uint8_t x, const uint8_t, const Color c);

	void testPalette();

	const std::array<Color, PALLET_SIZE> getColorPalette() const;

	const Color getPaletteColor(const uint16_t i) const;
	const Color getPaletteColor(const uint8_t x, const uint8_t y) const;

	inline const sf::Image getBuffer() const { return this->buffer; }
};