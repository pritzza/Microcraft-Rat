#include "Renderer.h"

#include "color/ColorPalette.h"

#include "../util/AABB.h"
#include "../util/Vector.h"

#include "../level/Level.h"
#include "../level/tile/Tile.h"

#include "../entity/Entity.h"

#include "../util/DeltaTime.h"

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
	const SpriteID id,
	const Vec2i& coords,
	const ColorPalette& cp,
	const RenderFlag rf,
	const Vec2i& displacement
)
{
	const Sprite& s{ sheet.getSprite(id) };

	const bool xFlip = static_cast<uint8_t>(rf) & static_cast<uint8_t>(RenderFlag::FLIP_X);
	const bool yFlip = static_cast<uint8_t>(rf) & static_cast<uint8_t>(RenderFlag::FLIP_Y);

	const Vec2i& cameraPos{ this->camera.getPos() };

	static constexpr int PIXELS_PER_BYTE{ SpriteSheet::getPixelsPerByte() };
	const uint8_t* const colorPaletteColorsStart{ cp.getColors() };

	// xy is offset of where sprite is being drawn on the buffer
	// ixy is the coord of the spritesheet pixel iterator
	for (int iy = 0; iy < s.h; ++iy)
		for (int ix = 0; ix < s.w; ++ix)
		{
			// current pixel's spritesheet x y pos
			const int shx{ ((xFlip ? ((s.x + s.w) - (ix + 1)) : s.x + ix) + displacement.x) / PIXELS_PER_BYTE };
			const int shy{ ( yFlip ? ((s.y + s.h) - (iy + 1)) : s.y + iy) + displacement.y };

			const Vec2i& placingPixelPositon{ (coords + Vec2i{ ix, iy }) - cameraPos };

			const int preFlipPixelIndex{ ix & (PIXELS_PER_BYTE - 1) };

			// terinary operator makes not ugly formatting hard
			const int pixelIndex{ 
				xFlip ? 
				PIXELS_PER_BYTE - (preFlipPixelIndex) - 1 : 
								   preFlipPixelIndex			// "& (PPB - 1)" as a slightly faster "% PPB"
			};

			this->putPixel(
				placingPixelPositon,
				*(colorPaletteColorsStart + (sheet.getPixel(shx, shy, pixelIndex)) )
					// can multiply/divide skx and sky to scale
			);
		}
}

void Renderer::render(const SpriteSheet& sheet, const World& world)
{
	for (const auto& [coords, chunk] : world.getChunks())
		//if (this->camera.isInView(Chunk::getAABB(coords)))
			for (int tileIndex = 0; tileIndex < Chunk::getSize(); ++tileIndex)
			{
				// setting up, getting all the tile's sprites and color palettes
				const Tile& tile{ chunk.getTile(tileIndex) };

				const TileBaseData& tileBase{ TileBases::getBase(tile.baseID) };
				const TileFeatureData& tileFeature{ TileFeatures::getFeature(tile.featureID) };

				// get tileFeature's sprite and palette
				const bool isTileFeatureValid{ tile.featureID != TileFeatures::ID::None };

				// LEN is the length the the tile's sprite in pixels in the spritesheet
				static constexpr int TILE_SPRITE_LEN{ SpriteSheet::getSprite(SpriteID::GroundTileBaseStart).w };

				// tileComponentIndex
				for (int compIndex = TileData::NUM_COMPONENTS - 1; compIndex >= 0; --compIndex)
				{
					// the tile component is drawn in respect to the position of its chunk, its tile and its compIndex
					const Vec2i tileComponentSpritePos{ getTileComponentSpritePosition(coords, tileIndex, compIndex) };

					const DetailedDirection d{ world.getTileDirection(coords, Vec2i::toVector(tileIndex, Chunk::getLength(), Chunk::getLength()), compIndex) };

					// calculating the crop offest for the tile's base's flavor
						// i dont know why we do -1					
					const Vec2i baseFlavorCropOffset{ Vec2i::toVector(tile.flavorBaseAnimationOffset + tile.flavors[compIndex] - 1, TileFlavor::DIMENSION, TileFlavor::DIMENSION) };
					const Vec2i baseCropOffset{ this->getTileBaseCropOffset(d, tile, compIndex, baseFlavorCropOffset) };
					
					// calculating the cropoffset for tile's base's flavor
					const Vec2i featureFlavorCropOffset{ Vec2i::toVector(tile.flavorFeatureAnimationOffset + tile.flavors[compIndex] - 1, TileFlavor::DIMENSION, TileFlavor::DIMENSION) };
					const bool isFeatureFlavored{ tileFeature.hasFlavors };
					const Vec2i featureCropOffset{ featureFlavorCropOffset * TILE_SPRITE_LEN * isFeatureFlavored };	// is either valid, or {0,0} depending on isFeatureFlavored

					// after all this prep, finally draw the tileBase, with either a directional or flavor crop

					// if the feature is totally opaque, you wont see the baseTile, so dont render it
					if (tileFeature.colorPalette.containsTransparency())
						this->render(sheet, tileBase.spriteID, tileComponentSpritePos, tileBase.colorPalette, RenderFlag::NONE, baseCropOffset);

					// if the tile/component has a valid feature to draw
					const bool drawFeatureOnComponent{
						isTileFeatureValid &&
							(
							(tile.featurePlacement[compIndex] && tileFeature.isSmall) ||
							(!tileFeature.isSmall && compIndex == 0)
							)
					};

					if (drawFeatureOnComponent)
						this->render(sheet, tileFeature.spriteID, tileComponentSpritePos, tileFeature.colorPalette, RenderFlag::NONE, featureCropOffset);
				}
			}
}

void Renderer::render(const SpriteSheet& sheet, const Level& level)
{
	this->render(sheet, level.getWorld());
}

// methods pertaining to render(world)
const Vec2i Renderer::getTileComponentSpritePosition(const Vec2i& chunkCoord, const int tileIndex, const int tileComponentIndex) const
{
	static constexpr int TILE_LEN{ SpriteSheet::getTileLength() };
	static constexpr int TILE_DIM{ TileData::DIMENSION };
	static constexpr int CHUNK_LEN{ Chunk::getLength() };

	// positional offset from chunk to chunk
	const Vec2i chunkOffset{ chunkCoord * CHUNK_LEN * TILE_LEN * TILE_DIM };

	// positional offset from tile to tile
	const Vec2i tileOffset{ Vec2i::toVector(tileIndex, CHUNK_LEN, CHUNK_LEN) * TILE_LEN * TILE_DIM };

	// positional offset from tile sprite to tile sprite (tile is made up for 4 sprites)
	const Vec2i tileSpriteOffset{ Vec2i::toVector(tileComponentIndex, TILE_DIM, TILE_DIM) * TILE_LEN };

	// final position
	return Vec2i{ chunkOffset + tileOffset + tileSpriteOffset };
}

const Vec2i Renderer::getTileBaseCropOffset(const DetailedDirection& dir, const Tile& tile, const int compIndex, const Vec2i& flavorCropOffset) const
{
	static constexpr int TILE_LEN{ SpriteSheet::getTileLength() };

	const TileBaseData& tileBase{ TileBases::getBase(tile.baseID) };

	// todo: make this a one liner and const
	TileFlavor animatedFlavor;
	animatedFlavor.setValue(tile.flavors[compIndex] + tile.flavorBaseAnimationOffset);

	// determines whether tile component should be cropped to have a flavor or a direction of a tile
	const bool cropTileBaseForFlavor
	{
		dir == DetailedDirection::Center &&			// is a center tile
		animatedFlavor.hasFlavor() &&				// has a flavor value
		tileBase.hasFlavors							// tileBase supports flavors};
	};

	// if cropTileBaseForFlavor, have the first line value, else, have the second line value
	const Vec2i baseCropOffset
	{
		((SpriteSheet::getTileBaseFlavorOffset() + flavorCropOffset)      * TILE_LEN) * (cropTileBaseForFlavor == true ) +
		((Directions::toVector(dir) + SpriteSheet::getTileCenterOffset()) * TILE_LEN) * (cropTileBaseForFlavor == false)
	};

	return baseCropOffset;
}

void Renderer::render(const SpriteSheet& sheet, const Entity& entity)
{
	const AnimatedSprite& animatedSprite{ entity.getAnimatedSprite() };
	const SpriteID& spriteID{ animatedSprite.getSpriteData().spriteID };
	const Sprite& sprite{ SpriteSheet::getSprite(spriteID) };

	const auto rf{ animatedSprite.getRenderFlags(entity.getDirection()) };
	const auto crop{ animatedSprite.getFrameCrop(entity.getDirection()) * sprite.w };

	const int dirIndex = SpriteSheet::getStandardAnimationDirectionIndex(entity.getDirection());
	const bool flipX = SpriteSheet::getStandardAnimationOrientation(entity.getDirection(), dirIndex);

	this->render(sheet, spriteID, entity.getPos(), ColorPalette{ 1000, 222, 333, 555 }, rf, crop);
}

// back to normal renderer methods
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
		static constexpr uint8_t COLOR_SCALING_FACTOR{ NORMAL_COLOR_MAX / Color::getColorRange() };

		// normalize each color channel from Color::MIN_VAL-Color::MAX_VAL to 0-255
		const uint8_t r = c.getRed()	* COLOR_SCALING_FACTOR;
		const uint8_t g = c.getGreen()  * COLOR_SCALING_FACTOR;
		const uint8_t b = c.getBlue()	* COLOR_SCALING_FACTOR;

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