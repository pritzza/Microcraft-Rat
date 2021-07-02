#pragma once

#include <string>

#include "Sprite.h"

// there is one sprite sheet that will always be stored during runtime
// it will store all the sprite data for every sprite
// sprites will be colored at runtime, so they're store in grayscale here
class SpriteSheet
{
private:
	// because a uint8_t is 8 bits, and we only need 2 bits to store one pixel
	// we can store 4 pixels in one uint8_t, so there are 4 pixels per element
	static constexpr uint8_t BYTE{ 8 };
	static constexpr uint8_t PIXEL_BIT_DEPTH{ 2 };	// takes 2 bits to store 1 pixel

	static constexpr uint8_t PIXELS_PER_BYTE{ sizeof(uint8_t) * BYTE / PIXEL_BIT_DEPTH };	// we store data for 4 pixels every 1 uint8_t

	static constexpr uint16_t SHEET_HEIGHT{ 256 };	// sprite sheet is 256x256 px (square)
	static constexpr uint16_t SHEET_WIDTH{ SHEET_HEIGHT / PIXELS_PER_BYTE };
	static constexpr uint16_t SHEET_SIZE{ SHEET_WIDTH * SHEET_HEIGHT };

	static constexpr uint8_t SPRITE_LENGTH{ 8 };	// px; used for locating and cropping sprites

private:
	enum Coords
	{
		SPRITE_X = 0 * SPRITE_LENGTH,
		SPRITE_Y = 0 * SPRITE_LENGTH,
	};
	enum Dimensions
	{
		SPRITE_W = 3 * SPRITE_LENGTH,
		SPRITE_H = 3 * SPRITE_LENGTH,
	};
	static constexpr Sprite SPRITES[]
	{
		{ SPRITE_X, SPRITE_Y, SPRITE_W, SPRITE_H },	// 0
	};
	
	static constexpr uint16_t NUM_SPRITES{ sizeof(SPRITES) / sizeof(Sprite) };

public:
	enum class SpriteID
	{
		Sprite	// 0
	};

private:
	uint8_t data[SHEET_WIDTH * SHEET_HEIGHT];

private:
	void loadFromFile(const std::string& fileName);

public:
	SpriteSheet(const std::string& fileName);

	const Sprite& getSprite(const SpriteSheet::SpriteID s) const;
	const uint8_t* const getData() const { return this->data; }
	const uint16_t getWidth() const { return this->SHEET_WIDTH; }
};