#pragma once

#include <string>

#include "../../util/Binary.h"
#include "../../util/Direction.h"
#include "../../util/Vector.h"

#include "Sprite.h"
#include "SpriteData.h"
#include "AnimatedSprite.h"

class Renderer;

// SpriteID gives an ID to atleast the beginning of every sprite
enum class SpriteID
{
	Sprite,					// 0
	GroundTileBaseStart,	// 1
	FlowerTileFeatureStart,	// 2
	TreeTileFeatureStart,	// 3
	PlayerStart				// 4
};

// AnimatedSpriteID gives IDs to all sprites that are meant to be animated
// I'm still not sure if tiles are meant to be here since so far, the only "tile animation"
// is a linear loop through all a tiles flavors (like water)
enum class AnimatedSpriteID
{
	Player,					// 0
};

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
	// "start" refers to the top left most cropped piece of the sprite
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
		TREE_FEATURE_START_X = 6 * SPRITE_LENGTH,
		TREE_FEATURE_START_Y = 12 * SPRITE_LENGTH,

		// player animated sprite
		PLAYER_START_X = 0 * SPRITE_LENGTH,
		PLAYER_START_Y = 0 * SPRITE_LENGTH,
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

		// player animated sprite
		PLAYER_START_W = 2 * SPRITE_LENGTH,
		PLAYER_START_H = 2 * SPRITE_LENGTH,
	};

	inline static constexpr Sprite SPRITES[]
	{																										// SpriteID s:
		{ SPRITE_X,			       SPRITE_Y,			   SPRITE_W,			 SPRITE_H				},	// 0 Sprite
		{ GROUND_BASE_START_X,     GROUND_BASE_START_Y,	   TILE_W,				 TILE_H					},	// 1 GroundTileBaseStart
		{ FLOWER_FEATURE_START_X,  FLOWER_FEATURE_START_Y, SMALL_TILE_FEATURE_H, SMALL_TILE_FEATURE_W	},	// 2 FlowerTileFeatureStart
		{ TREE_FEATURE_START_X,	   TREE_FEATURE_START_Y,   LARGE_TILE_FEATURE_H, LARGE_TILE_FEATURE_W	},	// 3 TreeTileFeature
		{ PLAYER_START_X,		   PLAYER_START_Y,		   PLAYER_START_W,		 PLAYER_START_H			},	// 4 Player
	};

	static constexpr uint16_t NUM_SPRITES{ sizeof(SPRITES) / sizeof(Sprite) };

	//inline static SpriteData spriteData[NUM_SPRITES];

private:
	inline static constexpr int NUM_STANDARD_ANIMATION_KEY_FRAMES{ 4 };

private:
	// imagine the first 4 frames of the player's animation are an array, from left to right
	// the first frame is them walking south, then north, then two frames of them walking east
	static inline constexpr Direction STANDARD_ANIMATION_DIRECTIONS[NUM_STANDARD_ANIMATION_KEY_FRAMES]
	{
		Direction::South,
		Direction::North,
		Direction::East,
		Direction::East
	};

	// on the south and north, or [0] and [1] frames, the keyframe/sprite doesnt change, it just flips
	// however on [2] and [3], to changes, so here is an array expresing the relation between each
	// keyframe in the animation "set" and which frames progress into which frames
	static inline constexpr int STANDARD_ANIMATION_PROGRESSION[NUM_STANDARD_ANIMATION_KEY_FRAMES]
	{
		0,		// 0	self referenching	(flips)
		1,		// 1	self referencing	(flips)
		3,		// 2	
		2		// 3
	};

	static inline constexpr AnimatedSpriteData ANIMATED_SPRITES[]
	{																// AnimatedSpriteID s:
		{ AnimationType::Standard, SpriteID::PlayerStart, 0.3f }	// 0 Player
	};

private:
	uint8_t data[SHEET_WIDTH * SHEET_HEIGHT];

private:
	void loadFromFile(const std::string& fileName);

public:
	SpriteSheet(const std::string& fileName);

	// renderer's main methods
	static constexpr Sprite getSprite(const SpriteID s)
	{
		return SPRITES[static_cast<int>(s)];
	}

	//inline const SpriteData& getSpriteData(const SpriteID id) const { return spriteData[static_cast<int>(id)]; }

	static constexpr AnimatedSpriteData getAnimatedSpriteData(const AnimatedSpriteID asID)
	{
		return ANIMATED_SPRITES[static_cast<int>(asID)];
	}
	
	// returns 2 bit pixel at index of xy coord
	const uint8_t getPixel(const uint16_t x, const uint16_t y, const uint8_t i) const
	{
		const int index{ x + (y * SHEET_WIDTH) };
		return (this->data[index] & (DETERMINING_BITS >> (i * PIXEL_BIT_DEPTH))) >> (((PIXELS_PER_BYTE - 1) - i) * PIXEL_BIT_DEPTH);
	}

	const uint8_t* const getData() const				{ return this->data;				 }

	static constexpr uint16_t getHeight()				{ return SHEET_HEIGHT;				 }
	static constexpr uint16_t getWidth()				{ return SHEET_WIDTH;				 }
	static constexpr uint8_t getPixelsPerByte()			{ return PIXELS_PER_BYTE;			 }

	// misc util sprite methods
	static constexpr Vec2i getSpriteDimensions(const SpriteID id)
	{
		const Sprite& s{ getSprite(id) };
		return Vec2i{ s.w, s.h };
	}
	static constexpr Vec2i getSpriteCoords(const SpriteID id)
	{
		const Sprite& s{ getSprite(id) };
		return Vec2i{ s.x, s.y };
	}

	// renderer's tile related methods
	static constexpr int getTileLength()				{ return TILE_W;					 }

	static constexpr Vec2i getTileCenterOffset()		{ return TILE_CENTER_OFFSET;		 }
	static constexpr Vec2i getTileBaseFlavorOffset()	{ return TILE_BASE_FLAVOR_OFFSET;	 }
	static constexpr Vec2i getTileFeatureFlavorOffset()	{ return TILE_FEATURE_FLAVOR_OFFSET; }

	// renderer's animation related methods
	static constexpr int getNumStandardAnimationKeyFrames()				  { return NUM_STANDARD_ANIMATION_KEY_FRAMES;		  }

	static constexpr Direction getStandardAnimationDirection(const int i) { return STANDARD_ANIMATION_DIRECTIONS[i];		  }
	static constexpr int getStandardAnimationProgression(const int i)	  { return STANDARD_ANIMATION_PROGRESSION[i];		  }

	static constexpr int getStandardAnimationDirectionIndex(const Direction dir)
	{
		for (int i = 0; i < NUM_STANDARD_ANIMATION_KEY_FRAMES; ++i)
		{
			if (STANDARD_ANIMATION_DIRECTIONS[i] == dir)
				return i;
			else if (i != STANDARD_ANIMATION_PROGRESSION[i])
				return i;
		}
	}

	static constexpr bool getStandardAnimationOrientation(const Direction dir, const int index)
	{
		return (STANDARD_ANIMATION_DIRECTIONS[index] == dir);
	}

	static constexpr bool isStandardAnimationFrameLooping(const int i)	  { return getStandardAnimationProgression(i) == i;   }
};