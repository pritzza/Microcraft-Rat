#pragma once

#include <string>

#include "../../util/Binary.h"
#include "../../util/Vector.h"

#include "Sprite.h"

class Renderer;

// there is one sprite sheet that will always be stored during runtime
// it will store all the sprite data for every sprite
// sprites will be colored at runtime, so they're store in grayscale here
class SpriteSheet
{
private:
	// because a uint8_t is 8 bits, and we only need 2 bits to store one pixel
	// we can store 4 pixels in one uint8_t, so there are 4 pixels per element
	static constexpr uint8_t PIXEL_BIT_DEPTH{ 2 };	// takes 2 bits to store 1 pixel

	static constexpr uint8_t PIXELS_PER_BYTE{ sizeof(uint8_t) * Binary::BYTE / PIXEL_BIT_DEPTH };	// we store data for 4 pixels every 1 uint8_t

	// we only care about the two leading bits
	// only used in sprite rendering and parsing spritesheet file
	static constexpr uint8_t DETERMINING_BITS{ 0b1100'0000 };

	static constexpr uint16_t SHEET_HEIGHT{ 256 };	// sprite sheet is 256x256 px (square)
	static constexpr uint16_t SHEET_WIDTH{ SHEET_HEIGHT / PIXELS_PER_BYTE };
	static constexpr uint16_t SHEET_SIZE{ SHEET_WIDTH * SHEET_HEIGHT };

	// each sprite's location in the spritesheet and its dimensions are a factor of this number
	static constexpr uint8_t SPRITE_LENGTH{ 8 };	// px; used for locating and cropping sprites

	static constexpr Vec2i TILE_CENTER_OFFSET{ 1, 1 };
	static constexpr Vec2i TILE_BASE_FLAVOR_OFFSET{ 0, 3 };
	static constexpr Vec2i TILE_FEATURE_FLAVOR_OFFSET{ 2, -1 };

private:
	enum Coords
	{
		// demo sprite
		SPRITE_X = 8 * SPRITE_LENGTH,
		SPRITE_Y = 0 * SPRITE_LENGTH,

		// the start of the 3x3 ground base tile, non flavor
		GROUND_BASE_START_X = 0 * SPRITE_LENGTH,
		GROUND_BASE_START_Y = 4 * SPRITE_LENGTH,

		// flower feature
		FLOWER_FEATURE_START_X = 0 * SPRITE_LENGTH,
		FLOWER_FEATURE_START_Y = 9 * SPRITE_LENGTH,

		// tree feature
		TREE_FEATURE_START_X = 0 * SPRITE_LENGTH,
		TREE_FEATURE_START_Y = 12 * SPRITE_LENGTH,
	};
	enum Dimensions
	{
		// demo sprite
		SPRITE_W = 2 * SPRITE_LENGTH,
		SPRITE_H = 2 * SPRITE_LENGTH,

		// all tile dimensions
		TILE_W = 1 * SPRITE_LENGTH,
		TILE_H = TILE_W,

		// small features that take up 1 tile component
		SMALL_TILE_FEATURE_W = TILE_W,
		SMALL_TILE_FEATURE_H = TILE_H,

		// large features that take up all 4 tile components/ a full tile
		LARGE_TILE_FEATURE_W = TILE_W * 2,
		LARGE_TILE_FEATURE_H = TILE_H * 2,
	};
	static constexpr Sprite SPRITES[]
	{
		{ SPRITE_X,			       SPRITE_Y,			   SPRITE_W,			 SPRITE_H				},	// 0
		{ GROUND_BASE_START_X,     GROUND_BASE_START_Y,	   TILE_W,				 TILE_H					},	// 1
		{ FLOWER_FEATURE_START_X,  FLOWER_FEATURE_START_Y, SMALL_TILE_FEATURE_H, SMALL_TILE_FEATURE_W	},	// 2
		{ TREE_FEATURE_START_X,	   TREE_FEATURE_START_Y,   LARGE_TILE_FEATURE_H, LARGE_TILE_FEATURE_W	},	// 3
	};
	
	static constexpr uint16_t NUM_SPRITES{ sizeof(SPRITES) / sizeof(Sprite) };

public:
	enum class SpriteID
	{
		Sprite,					// 0
		GroundTileBaseStart,	// 1
		FlowerTileFeatureStart,	// 2
		TreeTileFeatureStart,	// 3
	};

private:
	uint8_t data[SHEET_WIDTH * SHEET_HEIGHT];

private:
	void loadFromFile(const std::string& fileName);

public:
	SpriteSheet(const std::string& fileName);

	inline static constexpr Sprite getSprite(const SpriteSheet::SpriteID s)
	{
		return SPRITES[static_cast<uint8_t>(s)];
	}
	
	// returns 2 bit pixel at index of xy coord
	inline const uint8_t getPixel(const uint16_t x, const uint16_t y, const uint8_t i) const
	{
		const int index{ x + (y * SHEET_WIDTH) };
		return (this->data[index] & (DETERMINING_BITS >> (i * PIXEL_BIT_DEPTH))) >> (((PIXELS_PER_BYTE - 1) - i) * PIXEL_BIT_DEPTH);
	}

	inline const uint8_t* const getData() const					{ return this->data;				 }

	inline static constexpr uint16_t getHeight()				{ return SHEET_HEIGHT;				 }
	inline static constexpr uint16_t getWidth()					{ return SHEET_WIDTH;				 }
	inline static constexpr uint8_t getPixelsPerByte()			{ return PIXELS_PER_BYTE;			 }

	inline static constexpr Vec2i getTileCenterOffset()			{ return TILE_CENTER_OFFSET;		 }
	inline static constexpr Vec2i getTileBaseFlavorOffset()		{ return TILE_BASE_FLAVOR_OFFSET;	 }
	inline static constexpr Vec2i getTileFeatureFlavorOffset()	{ return TILE_FEATURE_FLAVOR_OFFSET; }

};