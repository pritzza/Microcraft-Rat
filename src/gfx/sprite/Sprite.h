#pragma once

#include "../../util/Vector.h"

class SpriteSheetData;

// a sprite is merely a struct that describes the position
// and dimensions of a region of pixels in the sprite sheet
// in the spritesheet class are defined an enum class of the sprites
// in the game, as well as where they reside in the game's spritesheet
struct Sprite
{
	// each sprite's location in the spritesheet and its dimensions are a factor of this number
	static constexpr uint8_t STANDARD_LENGTH{ 8 };	// px; used for locating and cropping sprites

	const Vec2i pos;	// pixel position of sprite's top left corner in spritesheet
	const Vec2i dim;	// dimensions of single sprite in pixels
	const Vec2i bounds;	// if a sprite is adjecnt to sprites that still represent one thing 
						// (ie all tile flavors) this is the dimensions of the sprites representing one thing in sprite (2x2 for tile flavors)

	// a sprite should never be made outside of the Spritesheet class (hence priv ctor and friend)
private:
	constexpr Sprite(const Vec2i& pos, const Vec2i& dim, const Vec2i& bounds)
		:
		pos{ pos },
		dim{ dim },
		bounds{ dim }
	{}

	friend class SpriteSheetData;
};