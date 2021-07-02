#pragma once

#include <SFML/Graphics/Image.hpp>

#include <array>
#include <cstdint>
#include <limits>

#include "Color.h"
#include "SpriteSheet.h"

class ColorPalette;

class Renderer
{
private:
	static constexpr uint16_t PALETTE_SIZE{ 256 };
	static constexpr uint8_t TRANSPARENT_COLOR_INDEX{ PALETTE_SIZE - 1 };
	
private:
	sf::Image buffer;

	const uint16_t bufferWidth;
	const uint16_t bufferHeight;
	const uint16_t bufferSize;

	std::array<Color, PALETTE_SIZE> colorPalette;
	uint8_t paletteUsed{};

private:
	void generateColorPalette();	// 6 for loops for each color channel

public:
	Renderer(const uint16_t width, const uint16_t height);

	void render(const SpriteSheet& sheet, const SpriteSheet::SpriteID id, const ColorPalette& cp, const uint16_t x, const uint16_t y);
	 
	// put a pixel on the image buffer
	void putPixel(const uint16_t bufferIndex, const uint8_t paletteIndex);
	void putPixel(const uint16_t i, const Color c);
	void putPixel(const uint16_t x, const uint16_t, const Color c);

	void testPalette();

	const std::array<Color, PALETTE_SIZE> getColorPalette() const;

	const Color getPaletteColor(const uint16_t i) const;
	const Color getPaletteColor(const uint8_t x, const uint8_t y) const;

	inline const sf::Image& getBuffer() const { return this->buffer; }
};