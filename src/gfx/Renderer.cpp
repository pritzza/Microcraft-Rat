#include "Renderer.h"

#include "color/ColorPalette.h"

#include "../util/AABB.h"
#include "../util/Vector.h"

#include "../level/Level.h"
#include "../level/Tiles.h"

#include <limits>
#include <cassert>

#include <iostream>

Renderer::Renderer(const uint16_t width, const uint16_t height)
	:
	bufferWidth( width ),
	bufferHeight( height ),
	bufferSize( width * height ),
	camera{ *this }
{
	static const sf::Color DEFAULT_BUFFER_COLOR{ 123,123,123 };
	this->buffer.create(width, height, DEFAULT_BUFFER_COLOR);
	generateColorPalette();
}

void Renderer::render(const SpriteSheet& sheet, const SpriteSheet::SpriteID id, const uint16_t x, const uint16_t y, const ColorPalette& cp, const RenderFlag rf)
{
	const Sprite& s{ sheet.getSprite(id) };
	//std::cout << static_cast<int>(id) << ": " << (int)s.h << '\n';

	const bool xFlip = static_cast<uint8_t>( rf ) & static_cast<uint8_t>( RenderFlag::FLIP_X );
	const bool yFlip = static_cast<uint8_t>( rf ) & static_cast<uint8_t>( RenderFlag::FLIP_Y );

	// xy is offset of where sprite is being drawn on the buffer
	// ixy is the coord of the spritesheet pixel iterator
	for (uint8_t ix = 0; ix < s.w; ++ix)
		for (uint8_t iy = 0; iy < s.h; ++iy)
		{
			// current pixel's spritesheet x y pos
			const uint8_t shx = (xFlip ? (s.x + s.w - ix - 1) : s.x + ix) / SpriteSheet::getPixelsPerByte();
			const uint8_t shy = (yFlip ? (s.y + s.h - iy - 1) : s.y + iy);

			this->putPixel(
				(x + ix) - this->camera.getPos().x,
				(y + iy) - this->camera.getPos().y,
				cp.getColors()
				[
					(sheet.getPixel(shx, shy, (0 + ix) % SpriteSheet::getPixelsPerByte()))
				]
			);
		}
}

void Renderer::render
(
	const SpriteSheet& sheet, 
	const SpriteSheet::SpriteID id,
	const Vec2i crop, 
	const Vec2i& coords, 
	const ColorPalette& cp, 
	const RenderFlag rf
)
{
}

void Renderer::render(const SpriteSheet& sheet, const Chunk& chunk, const Vec2i& coords)
{
	for (int i = 0; i < Chunk::getSize(); ++i)
	{
		// tiny abbreviations
		static constexpr int CHUNK_LEN{ Chunk::getLength() };

		const SpriteSheet::SpriteID& tileSpriteID{ chunk.getTile(i).spriteID };
		const ColorPalette& tileColorPalette{ chunk.getTile(i).colorPalette };

		// write a constant somewhere that makes the size of all tiles the same
		const uint8_t tileLen{ sheet.getSprite(tileSpriteID).w };

		// tile is drawn in accordance to its position within its chunk, and that respective
		// chunks position in the world

		const Vec2i chunkOffset{ coords * tileLen * CHUNK_LEN};
		const Vec2i tileOffset{ Vec2i::toVector(i, CHUNK_LEN, CHUNK_LEN) * tileLen };

		const Vec2i& pos{ chunkOffset + tileOffset };

		this->render(sheet, tileSpriteID, pos.x, pos.y, tileColorPalette);
	}
}

void Renderer::render(const SpriteSheet& sheet, const World& world)
{
	for (const auto& [coords, chunk] : world.getChunks())
		this->render(sheet, chunk, coords);
}

void Renderer::render(const SpriteSheet& sheet, const Level& level)
{
	this->render(sheet, level.getWorld());
}

void Renderer::generateColorPalette()
{
	static constexpr uint8_t min{ Color::getMinValue() };
	static constexpr uint8_t max{ Color::getMaxValue() };

	int paletteUsed{};

	// iterate through every rgb value and put it in the master colorPalette
	for (int r = min; r <= max; ++r)
		for (int g = min; g <= max; ++g)
			for (int b = min; b <= max; ++b)
				this->colorPalette[paletteUsed++].setData(r, g, b);

	// for transparency, we will make the last pixel of the palette the designated clear px
	this->colorPalette[TRANSPARENT_COLOR_INDEX].makeTransparent();
}

void Renderer::putPixel(const uint16_t i, const Color c)
{
	//const int x{ Vector2::toVectorX(i, bufferWidth, bufferHeight) };
	const uint16_t x = i % bufferWidth;
	const uint16_t y = i / bufferWidth;

	this->putPixel(x, y, c);
}

void Renderer::putPixel(const uint16_t i, const uint8_t colorIndex)
{
	this->putPixel(i, this->colorPalette[colorIndex]);
}

void Renderer::putPixel(const uint16_t x, const uint16_t y, const uint8_t colorIndex)
{
	this->putPixel(x, y, this->colorPalette[colorIndex]);
}

void Renderer::putPixel(const uint16_t x, const uint16_t y, const Color c)
{
	if (!c.isTransparent() && AABB::isPointInside(x, y, 0, 0, bufferWidth-1, bufferHeight-1))
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

const int Renderer::getPaletteIndex(const Color& c) const
{
	static constexpr uint8_t CR{ Color::getColorRange() };

	// when we generate the color palette, its a triple for loop going r g b
	// this is kinda how we reverse engineer the indices of the color palette
	return (c.getRed() * CR * CR) + (c.getGreen() * CR) + c.getBlue();
}