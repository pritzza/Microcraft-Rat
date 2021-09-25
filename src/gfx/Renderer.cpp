#include "Renderer.h"

#include "color/ColorPalette.h"

#include "sprite/SpriteCropper.h"

#include "sheet/SpriteSheetAnimationData.h"
#include "sheet/SpriteSheetData.h"

#include "../util/AABB.h"
#include "../util/Vector.h"

#include "../level/Level.h"
#include "../level/tile/Tile.h"

#include "../entity/Entity.h"

#include <limits>
#include <cassert>

#include <iostream>

Renderer::Renderer(const SpriteSheet& sheet, const uint16_t width, const uint16_t height)
	:
	sheet{ sheet },
	bufferWidth(width),
	bufferHeight(height),
	bufferSize(width* height),
	camera{ *this }
{
	static const sf::Color DEFAULT_BUFFER_COLOR{ 123,123,123 };
	this->buffer.create(width, height, DEFAULT_BUFFER_COLOR);
	generateColorPalette();
}

void Renderer::render(const SpriteRenderArgs& args)
{
	const Sprite& s{ SpriteSheetData::getSprite(args.id) };

	const bool xFlip = static_cast<uint8_t>(args.rf) & static_cast<uint8_t>(RenderFlag::FLIP_X);
	const bool yFlip = static_cast<uint8_t>(args.rf) & static_cast<uint8_t>(RenderFlag::FLIP_Y);

	const Vec2i& cameraPos{ this->camera.getPos() };

	static constexpr int PIXELS_PER_BYTE{ SpriteSheet::getPixelsPerByte() };
	const uint8_t* const colorPaletteColorsStart{ args.cp.getColors() };

	// xy is offset of where sprite is being drawn on the buffer
	// ixy is the coord of the spritesheet pixel iterator
	for (int iy = 0; iy < s.h; ++iy)
		for (int ix = 0; ix < s.w; ++ix)
		{
			// current pixel's spritesheet x y pos
			const int shx{ ((xFlip ? ((s.x + s.w) - (ix + 1)) : s.x + ix) + args.displacement.x) / PIXELS_PER_BYTE };
			const int shy{ (yFlip ? ((s.y + s.h) - (iy + 1)) : s.y + iy) + args.displacement.y };

			const Vec2i& placingPixelPositon{ (args.coords + Vec2i{ ix, iy }) - cameraPos };

			const int preFlipPixelIndex{ ix & (PIXELS_PER_BYTE - 1) }; // "& (PPB - 1)" as a slightly faster "% PPB"

			// terinary operator makes not ugly formatting hard
			const int pixelIndex{
				xFlip ?
				PIXELS_PER_BYTE - (preFlipPixelIndex)-1 :
				preFlipPixelIndex
			};

			this->putPixel(
				placingPixelPositon,
				*(colorPaletteColorsStart + (sheet.getPixel(shx, shy, pixelIndex)))
				// can multiply/divide skx and sky to scale
			);
		}
}

void Renderer::render(const World& world)
{
	for (const auto& [coords, chunk] : world.getChunks())
	{
		static constexpr int CHUNK_LEN{ Chunk::getPixelLength() };

		const AABB chunkBounds{
			coords.x * CHUNK_LEN,
			coords.y * CHUNK_LEN,
			CHUNK_LEN,
			CHUNK_LEN
		};

		if (camera.isInView(chunkBounds))
			for (int tileIndex = 0; tileIndex < Chunk::getSize(); ++tileIndex)
			{
				// setting up, getting all the tile's sprites and color palettes
				const Tile& tile{ chunk.getTile(tileIndex) };

				const bool tileHasFeature{ tile.hasFeature() };
				const int tileFeatureSpriteLength{ tile.getFeature().sprite.getDimensions().x };

				// tileComponentIndex, go in reverse so large sprites (like tree) dont get overlapped/overwritten by tiles or other things
				for (int compIndex = TileData::NUM_COMPONENTS - 1; compIndex >= 0; --compIndex)
				{
					// the tile component is drawn in respect to the position of its chunk, its tile and its compIndex
					const Vec2i tileComponentSpritePos{ world.getTileComponentPixelPos(coords, tileIndex, compIndex) };

					// draw tileBase
					renderTileBase(tile, compIndex, tileComponentSpritePos, world, coords, tileIndex);

					// draw tileFeature
					renderTileFeature(tile, compIndex, tileComponentSpritePos, tileFeatureSpriteLength, tileHasFeature);
				}
			}
	}
}

void Renderer::renderTileBase(
	const Tile& tile,
	const int compIndex,
	const Vec2i& spritePos,
	const World& world,
	const Vec2i& chunkCoords,
	const int tileIndex
)
{
	// prep
	SpriteCropper sc;

	static constexpr int TILE_SPRITE_LEN{ SpriteSheetData::getTileLength() };

	// tile base render logic (make functions)
	const AABB baseBounds{ spritePos.x, spritePos.y, TILE_SPRITE_LEN, TILE_SPRITE_LEN };

	if (camera.isInView(baseBounds))
	{
		const TileBase& tileBase{ tile.getBase() };

		const SpriteID sprite{ tileBase.sprite.getSpriteData().spriteID };
		const ColorPalette& colorPalette{ tileBase.getData().colorPalette };
		const Vec2i cropOffset{ sc.getTileBaseOffset(tile, compIndex, world, chunkCoords, tileIndex) };

		// if the feature is totally opaque, you wont see the baseTile, so dont render it
		if (!colorPalette.containsTransparency())
			this->renderingQueue.push({ sprite, spritePos, colorPalette, RenderFlag::NONE, cropOffset });
	}
}

void Renderer::renderTileFeature(const Tile& tile, const int compIndex, const Vec2i& spritePos, const int spriteLen, const bool hasFeature)
{
	SpriteCropper sc;

	// tile feature render logic (make function)
	const AABB featureBounds{ spritePos.x, spritePos.y, spriteLen, spriteLen };

	if (hasFeature && camera.isInView(featureBounds))
	{
		const TileFeature& tileFeature{ tile.getFeature() };
		const bool isFeatureSmall{ tileFeature.getData().isSmall };

		// if the tile/component has a valid feature to draw
		// terrible formatting lmao
		const bool drawOnComponent{
				( isFeatureSmall) && tileFeature.isOnComponent[compIndex] ||
				(!isFeatureSmall  && compIndex == 0)
		};

		if (drawOnComponent)
		{
			const SpriteID sprite{ tileFeature.sprite.getSpriteData().spriteID };
			const ColorPalette& colorPalette{ tileFeature.getData().colorPalette };
			const Vec2i cropOffset{ sc.getTileFeatureOffset(tile, compIndex, spriteLen) };

			this->renderingQueue.push({ sprite, spritePos, colorPalette, RenderFlag::NONE, cropOffset });
		}
	}
}

void Renderer::render(const Level& level)
{
	this->render(level.getWorld());
}

void Renderer::renderQueue()
{
	//std::cout << "sprites: " << renderingQueue.size() << '\n';
	while (!this->renderingQueue.empty())
	{
		this->render(renderingQueue.front());
		renderingQueue.pop();
	}
}

void Renderer::render(const Entity& entity)
{
	const AnimatedSprite& animatedSprite{ entity.getAnimatedSprite() };

	const SpriteID spriteID{ animatedSprite.getSpriteData().spriteID };
	const Sprite& sprite{ SpriteSheetData::getSprite(spriteID) };

	const RenderFlag rf{ animatedSprite.getRenderFlags() };
	const Vec2i crop{ animatedSprite.getFrameIndex() * sprite.w, 0 };

	this->renderingQueue.push({ spriteID, entity.getPos(), entity.getPalette(), rf, crop });
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
	if (!c.isTransparent() && AABB::isPointInside(coords.x, coords.y, 0, 0, bufferWidth - 1, bufferHeight - 1))
	{
		static constexpr uint8_t NORMAL_COLOR_MAX{ std::numeric_limits<uint8_t>::max() };
		static constexpr uint8_t COLOR_SCALING_FACTOR{ NORMAL_COLOR_MAX / Color::getColorRange() };

		// normalize each color channel from Color::MIN_VAL-Color::MAX_VAL to 0-255
		const uint8_t r = c.getRed() * COLOR_SCALING_FACTOR;
		const uint8_t g = c.getGreen() * COLOR_SCALING_FACTOR;
		const uint8_t b = c.getBlue() * COLOR_SCALING_FACTOR;

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