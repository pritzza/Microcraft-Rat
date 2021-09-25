#pragma once

#include <SFML/Graphics/Image.hpp>

#include <array>
#include <cstdint>
#include <limits>

#include <queue>

#include "color/Color.h"
#include "sheet/SpriteSheet.h"

#include "Camera.h"

class ColorPalette;

struct Vec2i;

class Level;
struct Chunk;
class World;
class Tile;

class Entity;

enum class DetailedDirection;

enum class SpriteID;

enum class RenderFlag
{
	NONE = 0b00,
	FLIP_X = 0b01,
	FLIP_Y = 0b10,
	FLIP_BOTH = FLIP_X | FLIP_Y
};

struct SpriteRenderArgs
{
	const SpriteID id;
	const Vec2i coords;
	const ColorPalette& cp;
	const RenderFlag rf = RenderFlag::NONE;
	const Vec2i displacement = Vec2i{ 0, 0 };
};

class Renderer
{
private:
	static constexpr uint16_t PALETTE_SIZE{ 256 };
	static constexpr uint8_t TRANSPARENT_COLOR_INDEX{ PALETTE_SIZE - 1 };

private:
	sf::Image buffer;

	std::queue<SpriteRenderArgs> renderingQueue;

	const uint16_t bufferWidth;
	const uint16_t bufferHeight;
	const uint16_t bufferSize;

	Camera camera;

	// we store the entire color palette in memory here,
	// but we could also just not and figure out colors at runtime
	std::array<Color, PALETTE_SIZE> colorPalette;

	const SpriteSheet& sheet;

private:
	void generateColorPalette();	// 6 for loops for each color channel

	void renderTileBase(const Tile& tile, const int compIndex, const Vec2i& spritePos, const World& world, const Vec2i& chunkCoords, const int tileIndex);
	void renderTileFeature(const Tile& tile, const int compIndex, const Vec2i& spritePos, const int spriteLen, const bool hasFeature);

	void render(const SpriteRenderArgs& args);

public:
	Renderer(const SpriteSheet& sheet, const uint16_t width, const uint16_t height);

	void render(const World& world);
	void render(const Level& level);

	void render(const Entity& entity);

	// actually renders everything in the renderingQueue. Must be called for anything to appear
	void renderQueue();

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