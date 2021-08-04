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
	for (int iy = 0; iy < s.h; ++iy)
		for (int ix = 0; ix < s.w; ++ix)
		{
			// current pixel's spritesheet x y pos
			const int shx = ((xFlip ? (s.x + s.w - ix - 1) : s.x + ix) + displacement.x) / SpriteSheet::getPixelsPerByte();
			const int shy =  (yFlip ? (s.y + s.h - iy - 1) : s.y + iy) + displacement.y;

			const Vec2i& placingPixelPositon{ (coords + Vec2i{ ix, iy }) - this->camera.getPos() };

			this->putPixel(
				placingPixelPositon,
				cp.getColors()
				[
					// can multiply/divide skx and sky to scale
					(sheet.getPixel(shx, shy, ix % SpriteSheet::getPixelsPerByte()))
				]
			);
		}
}

void Renderer::render(const SpriteSheet& sheet, const World& world)
{
	for (const auto& [coords, chunk] : world.getChunks())
		//if (this->camera.isInView(Chunk::getAABB(coords)))
			for (int i = 0; i < Chunk::getSize(); ++i)
			{
				// get tileNase's sprite and palette
				const SpriteSheet::SpriteID& tileBaseSpriteID{ TileBases::getBase(chunk.getTileBaseID(i)).spriteID };
				const ColorPalette& tileBaseColorPalette{ TileBases::getBase(chunk.getTileBaseID(i)).colorPalette };

				// get tileFeature's sprite and palette
				const bool isTileFeatureValid{ chunk.getTileFeatureID(i) != TileFeatures::ID::None };
				const SpriteSheet::SpriteID& tileFeatureSpriteID{ TileFeatures::getFeature(chunk.getTileFeatureID(i)).spriteID };
				const ColorPalette& tileFeatureColorPalette{ TileFeatures::getFeature(chunk.getTileFeatureID(i)).colorPalette };

				// tiny abbreviations:
					// LEN is the length the the tile's sprite in pixels in the spritesheet
					// DIM is the ammount of "tile components" in one axis that make up a tile
				static constexpr int TILE_LEN{ SpriteSheet::getSprite(SpriteSheet::SpriteID::GroundTileBaseStart).w };
				static constexpr int TILE_DIM{ TileData::DIMENSION };
				static constexpr int CHUNK_LEN{ Chunk::getLength() };

				// tile is drawn in accordance to its position within its chunk, and that respective
				// chunks position in the world
				for (int j = 0; j < TileData::NUM_COMPONENTS; ++j)
				{
					// positional offset from chunk to chunk
					const Vec2i chunkOffset{ coords * TILE_LEN * CHUNK_LEN * TILE_DIM };

					// positional offset from tile to tile
					const Vec2i tileOffset{ Vec2i::toVector(i, CHUNK_LEN, CHUNK_LEN) * TILE_LEN * TILE_DIM };

					// positional offset from tile sprite to tile sprite (tile is made up for 4 sprites)
					const Vec2i tileSpriteOffset{ Vec2i::toVector(j, TILE_DIM, TILE_DIM) * TILE_LEN};

					const Vec2i& pos{ chunkOffset + tileOffset + tileSpriteOffset };

					const DetailedDirection d{ world.getTileDirection(coords, Vec2i::toVector(i, CHUNK_LEN, CHUNK_LEN), j) };

					const Vec2i flavorCropOffset{ Vec2i::toVector(static_cast<int>(chunk.getTile(i).flavors[j]) - 2, TileFlavor::DIMENSION, TileFlavor::DIMENSION) };
					Vec2i baseCropOffset{0,0};

					// only give tilebase flavor if
					if (
						d == DetailedDirection::Center									// is a center tile
						&& chunk.getTile(i).flavors[j] != TileFlavor::Value::None &&	// has a flavor value
						TileBases::getBase(chunk.getTileBaseID(coords)).hasFlavors		// tileBase supports flavors
						)
						baseCropOffset = (SpriteSheet::getTileFlavorOffset() + flavorCropOffset) * TILE_LEN;
					else	// else, give non flavor crop (directional based) 
						baseCropOffset = (Directions::toVector(d) + SpriteSheet::getTileCenterOffset()) * TILE_LEN;

					const bool isFeatureFlavored{ TileFeatures::getFeature(chunk.getTileFeatureID(coords)).hasFlavors };

					const Vec2i featureCropOffset{ flavorCropOffset * isFeatureFlavored * TILE_LEN };

					this->render(sheet, tileBaseSpriteID, pos, tileBaseColorPalette, RenderFlag::NONE, baseCropOffset);

					if (isTileFeatureValid && chunk.getTile(i).featurePlacement[j])
						this->render(sheet, tileFeatureSpriteID, pos, tileFeatureColorPalette, RenderFlag::NONE, featureCropOffset);
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