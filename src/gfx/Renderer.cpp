#include "Renderer.h"

#include "color/ColorPalette.h"

#include "../util/AABB.h"
#include "../util/Vector.h"

#include "../level/Level.h"
#include "../level/tile/Tile.h"

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

void Renderer::render
(
	const SpriteSheet& sheet,
	const SpriteSheet::SpriteID id,
	const Vec2i& coords,
	const ColorPalette& cp,
	const RenderFlag rf,
	const Vec2i& displacement
)
{
	const Sprite& s{ sheet.getSprite(id) };

	const bool xFlip = static_cast<uint8_t>(rf) & static_cast<uint8_t>(RenderFlag::FLIP_X);
	const bool yFlip = static_cast<uint8_t>(rf) & static_cast<uint8_t>(RenderFlag::FLIP_Y);

	// xy is offset of where sprite is being drawn on the buffer
	// ixy is the coord of the spritesheet pixel iterator
	for (uint8_t ix = 0; ix < s.w; ++ix)
		for (uint8_t iy = 0; iy < s.h; ++iy)
		{
			// current pixel's spritesheet x y pos
			const uint8_t shx = ((xFlip ? (s.x + s.w - ix - 1) : s.x + ix) + displacement.x) / SpriteSheet::getPixelsPerByte();
			const uint8_t shy =  (yFlip ? (s.y + s.h - iy - 1) : s.y + iy) + displacement.y;

			const Vec2i& placingPixelPositon{ (coords + Vec2i{ ix, iy }) - this->camera.getPos() };

			this->putPixel(
				placingPixelPositon,
				cp.getColors()
				[
					(sheet.getPixel(shx, shy, ix % SpriteSheet::getPixelsPerByte()))
				]
			);
		}
}

void Renderer::render(const SpriteSheet& sheet, const World& world)
{
	for (const auto& [coords, chunk] : world.getChunks())
		for (int i = 0; i < Chunk::getSize(); ++i)
		{
			// tiny abbreviations
			static constexpr int CHUNK_LEN{ Chunk::getLength() };
			static constexpr int TILE_DIM{ TileData::SPRITE_DIMENSIONS };

			// get tileNase's sprite and palette
			const SpriteSheet::SpriteID& tileBaseSpriteID{ TileBases::getBase(chunk.getTileBaseID(i)).spriteID };
			const ColorPalette& tileBaseColorPalette{ TileBases::getBase(chunk.getTileBaseID(i)).colorPalette };

			// get tileFeature's sprite and palette
			const bool isTileFeatureValid{ chunk.getTileFeatueID(i) != TileFeatures::ID::None };
			const SpriteSheet::SpriteID& tileFeatureSpriteID{ TileFeatures::getFeature(chunk.getTileFeatueID(i)).spriteID };
			const ColorPalette& tileFeatureColorPalette{ TileFeatures::getFeature(chunk.getTileFeatueID(i)).colorPalette };

			static constexpr int tileLen{ SpriteSheet::getSprite(SpriteSheet::SpriteID::GroundTileBase).w };

			// tile is drawn in accordance to its position within its chunk, and that respective
			// chunks position in the world
			for (int j = 0; j < TILE_DIM * TILE_DIM; ++j)
			{
				// positional offset from chunk to chunk
				const Vec2i chunkOffset{ coords * tileLen * CHUNK_LEN * TILE_DIM };

				// positional offset from tile to tile
				const Vec2i tileOffset{ Vec2i::toVector(i, CHUNK_LEN, CHUNK_LEN) * tileLen * TILE_DIM };

				// positional offset from tile sprite to tile sprite (tile is made up for 4 sprites)
				const Vec2i tileSpriteOffset{ Vec2i::toVector(j, TILE_DIM, TILE_DIM) * tileLen };

				const Vec2i& pos{ chunkOffset + tileOffset + tileSpriteOffset };

				const DetailedDirection d{ world.getTileDirection(coords, Vec2i::toVector(i, CHUNK_LEN, CHUNK_LEN), j) };

				// + 1 so that d 0,0 is the center of the tilesprite in the actual spritesheet
				const Vec2i cropOffset{ (Directions::toVector(d) + 1) * tileLen };

				this->render(sheet, tileBaseSpriteID, pos, tileBaseColorPalette, RenderFlag::NONE, cropOffset);

				if (isTileFeatureValid)
					this->render(sheet, tileFeatureSpriteID, pos, tileFeatureColorPalette, RenderFlag::NONE, cropOffset);
			}
		}
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
	const Vec2i pos{ Vec2i::toVector(i, bufferWidth, bufferHeight) };

	this->putPixel(pos, c);
}

void Renderer::putPixel(const uint16_t i, const uint8_t colorIndex)
{
	this->putPixel(i, this->colorPalette[colorIndex]);
}

void Renderer::putPixel(const Vec2i& coords, const uint8_t colorIndex)
{
	this->putPixel(coords, this->colorPalette[colorIndex]);
}

void Renderer::putPixel(const Vec2i& coords, const Color c)
{
	if (!c.isTransparent() && AABB::isPointInside(coords.x, coords.y, 0, 0, bufferWidth-1, bufferHeight-1))
	{
		static constexpr uint8_t NORMAL_COLOR_MAX{ std::numeric_limits<uint8_t>::max() };

		// normalize each color channel from Color::MIN_VAL-Color::MAX_VAL to 0-255
		const uint8_t r = (c.getRed()	* NORMAL_COLOR_MAX) / Color::getColorRange();
		const uint8_t g = (c.getGreen() * NORMAL_COLOR_MAX) / Color::getColorRange();
		const uint8_t b = (c.getBlue()	* NORMAL_COLOR_MAX) / Color::getColorRange();

		// the renderer's buffer contains the pixel data that is going on the screen
		// so here is where we are actually telling which pixel goes on the screen
		this->buffer.setPixel(coords.x, coords.y, sf::Color{ r, g, b });
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