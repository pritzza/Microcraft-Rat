#pragma once

#include <SFML/Graphics/Image.hpp>

#include <array>
#include <cstdint>
#include <limits>

#include "color/Color.h"
#include "sprite/SpriteSheet.h"

#include "Camera.h"

class ColorPalette;

struct Vec2i;

class Level;
struct Chunk;
class World;
class Tile;

enum class DetailedDirection;

enum class RenderFlag
{
	NONE = 0b00,
	FLIP_X = 0b01,
	FLIP_Y = 0b10,
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

	Camera camera;

	// we store the entire color palette in memory here,
	// but we could also just not and figure out colors at runtime
	std::array<Color, PALETTE_SIZE> colorPalette;

private:
	void generateColorPalette();	// 6 for loops for each color channel

	// functions for render(world)
	const Vec2i getTileComponentSpritePosition(const Vec2i& chunkCoord, const int tileIndex, const int tileComponentIndex) const;
	const Vec2i getTileBaseCropOffset(const DetailedDirection& dir, const Tile& tile, const int compIndex, const Vec2i& flavorCropOffset) const;

public:
	Renderer(const uint16_t width, const uint16_t height);

	// for rendering any ol' static sprite
	void render
	(
		const SpriteSheet& sheet,
		const SpriteSheet::SpriteID id,
		const Vec2i& coords,
		const ColorPalette& cp,
		const RenderFlag rf = RenderFlag::NONE,
		const Vec2i & displacement = Vec2i{0, 0}
	);

	void render(const SpriteSheet& sheet, const World& world);
	void render(const SpriteSheet& sheet, const Level& level);

	// put a pixel on the image buffer
	void putPixel(const uint16_t i, const Color c);
	void putPixel(const uint16_t i, const uint8_t colorIndex);
	void putPixel(const Vec2i& coords, const Color c);
	void putPixel(const Vec2i& coords, const uint8_t colorIndex);

	void testPalette();

	inline Camera& getCamera()									{ return this->camera;			  }

	const int getPaletteIndex(const Color& c) const;

	inline const Color getPaletteColor(const uint16_t i) const  { return this->colorPalette[i];   }

	inline const sf::Image& getBuffer() const					{ return this->buffer;			  }
	inline const uint16_t getBufferWidth() const				{ return this->bufferWidth;		  }
	inline const uint16_t getBufferHeight() const				{ return this->bufferHeight;	  }

	inline static constexpr uint8_t getTransparentColor()		{ return TRANSPARENT_COLOR_INDEX; }

};