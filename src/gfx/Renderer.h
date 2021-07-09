#pragma once

#include <SFML/Graphics/Image.hpp>

#include <array>
#include <cstdint>
#include <limits>

#include "Color.h"
#include "SpriteSheet.h"

class ColorPalette;
struct Vec2i;
struct Chunk;
class Level;
class World;

enum class RenderFlag
{
	NONE	  = 0b00,
	FLIP_X	  = 0b01,
	FLIP_Y	  = 0b10,
	FLIP_BOTH = FLIP_X | FLIP_Y
};

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

	// we store the entire color palette in memory here,
	// but we could also just not and figure out colors at runtime
	std::array<Color, PALETTE_SIZE> colorPalette;
	uint8_t paletteUsed{};

private:
	void generateColorPalette();	// 6 for loops for each color channel

public:
	Renderer(const uint16_t width, const uint16_t height);

	void render(
		const SpriteSheet& sheet, 
		const SpriteSheet::SpriteID id, 
		const uint16_t x, 
		const uint16_t y,
		const ColorPalette& cp, 
		const RenderFlag rf = RenderFlag::NONE
		);

	void render(const SpriteSheet& sheet, const Chunk& chunk, const Vec2i& coords);
	void render(const SpriteSheet& sheet, const World& world);
	void render(const SpriteSheet& sheet, const Level& level);
	 
	// put a pixel on the image buffer
	//void putPixel(const uint16_t bufferIndex, const uint8_t paletteIndex);
	void putPixel(const uint16_t i, const Color c);
	void putPixel(const uint16_t i, const uint8_t colorIndex);
	void putPixel(const uint16_t x, const uint16_t, const Color c);
	void putPixel(const uint16_t x, const uint16_t, const uint8_t colorIndex);

	void testPalette();

	//const std::array<Color, PALETTE_SIZE> getColorPalette() const;
	//
	inline const Color getPaletteColor(const uint16_t i) const { return this->colorPalette[i]; }
	const int getPaletteIndex(const Color& c) const;

	inline const sf::Image& getBuffer() const { return this->buffer; }

	inline static constexpr uint8_t getTransparentColor() { return TRANSPARENT_COLOR_INDEX; }

};