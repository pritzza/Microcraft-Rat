#pragma once

#include "../sprite/Sprite.h"
#include "../sprite/SpriteData.h"	

#include "../../util/Vector.h"

// SpriteID gives an ID to atleast the beginning of every sprite
enum class SpriteID
{
	Sprite,					// 0
	GroundTileBaseStart,	// 1
	FlowerTileFeatureStart,	// 2
	TreeTileFeatureStart,	// 3
	PlayerStart				// 4
};

class SpriteSheetData
{
	//inline static SpriteData spriteData[NUM_SPRITES];

	// each sprite's location in the spritesheet and its dimensions are a factor of this number
	static constexpr uint8_t SPRITE_LENGTH{ 8 };	// px; used for locating and cropping sprites

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
		FLOWER_FEATURE_START_X = 4 * SPRITE_LENGTH,
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

	static constexpr Vec2i TILE_CENTER_OFFSET		 { 1,  1 };	// topleft tile base sprite to center  tile base sprite
	static constexpr Vec2i TILE_BASE_FLAVOR_OFFSET	 { 0,  3 };	// topleft tile base sprite to topleft tile base flavors
	static constexpr Vec2i TILE_FEATURE_FLAVOR_OFFSET{ 2, -1 };	// topleft tile flavor sprite to topleft of tile feature flavors

public:
	// used primarily in renderer to access Sprite members
	static constexpr Sprite getSprite(const SpriteID s)
	{
		return SPRITES[static_cast<int>(s)];
	}

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

	// tile related methods
	static constexpr int getTileLength()				{ return TILE_W;					 }

	static constexpr Vec2i getTileCenterOffset()		{ return TILE_CENTER_OFFSET;		 }
	static constexpr Vec2i getTileBaseFlavorOffset()	{ return TILE_BASE_FLAVOR_OFFSET;	 }
	static constexpr Vec2i getTileFeatureFlavorOffset()	{ return TILE_FEATURE_FLAVOR_OFFSET; }

};