#pragma once

#include <cstdint>

class SpriteSheet;

// a sprite is merely a struct that describes the position
// and dimensions of a region of pixels in the sprite sheet
// in the spritesheet class are defined an enum class of the sprites
// in the game, as well as where they reside in the game's spritesheet
struct Sprite
{
	// sprite sheet x/y start, width/height
	uint8_t x, y, w, h;

	// a sprite should never be made outside of the Spritesheet class (hence priv ctor and friend)
private:
	constexpr Sprite(const uint8_t x, const uint8_t y, const uint8_t w, const uint8_t h)
		:
		x{ x },
		y{ y },
		w{ w },
		h{ h }
	{}

	friend class SpriteSheet;
};