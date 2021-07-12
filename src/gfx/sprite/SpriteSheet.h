#pragma once

#include <string>

#include "../../util/Binary.h"

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

private:
	enum Coords
	{
		// demo sprite
		SPRITE_X = 1 * SPRITE_LENGTH,
		SPRITE_Y = 0 * SPRITE_LENGTH,

		// ground tile
		GROUND_X = 0 * SPRITE_LENGTH,
		GROUND_Y = 3 * SPRITE_LENGTH,
	};
	enum Dimensions
	{
		// demo sprite
		SPRITE_W = 2 * SPRITE_LENGTH,
		SPRITE_H = 2 * SPRITE_LENGTH,

		// Ground Tile (should have seame length)
		GROUND_W = 1 * SPRITE_LENGTH,
		GROUND_H = 1 * SPRITE_LENGTH,
	};
	static constexpr Sprite SPRITES[]
	{
		{ SPRITE_X, SPRITE_Y, SPRITE_W, SPRITE_H },	// 0
		{ GROUND_X, GROUND_Y, GROUND_W, GROUND_H },	// 1
	};
	
	static constexpr uint16_t NUM_SPRITES{ sizeof(SPRITES) / sizeof(Sprite) };

public:
	enum class SpriteID
	{
		Sprite,		// 0
		GroundTile,	// 1
	};

private:
	uint8_t data[SHEET_WIDTH * SHEET_HEIGHT];

private:
	void loadFromFile(const std::string& fileName);

public:
	SpriteSheet(const std::string& fileName);

	const Sprite& getSprite(const SpriteSheet::SpriteID s) const;
	
	// returns 2 bit pixel at index of xy coord
	const uint8_t getPixel(const uint16_t x, const uint16_t y, const uint8_t i) const;

	inline const uint8_t* const getData() const		   { return this->data;		 }

	inline static constexpr uint16_t getHeight()	   { return SHEET_HEIGHT;	 }
	inline static constexpr uint16_t getWidth()		   { return SHEET_WIDTH;	 }
	inline static constexpr uint8_t getPixelsPerByte() { return PIXELS_PER_BYTE; }
};