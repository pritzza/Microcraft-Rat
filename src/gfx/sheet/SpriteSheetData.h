#pragma once

#include "../sprite/Sprite.h"
#include "../sprite/SpriteData.h"	

#include "../../util/Vector.h"

// SpriteID gives an ID to atleast the beginning of every sprite
enum class SpriteID
{
	Sprite,					// 0
	GroundTileBase,			// 1
	FlowerTileFeature,		// 2
	TreeTileFeature,		// 3
	Player,					// 4
	GroundTileBaseFeature,	// 5
};

class SpriteSheetData
{
	//inline static SpriteData spriteData[NUM_SPRITES];

	// each sprite's location in the spritesheet and its dimensions are a factor of this number
	static constexpr uint8_t S_LEN{ Sprite::STANDARD_LENGTH };	// px; used for locating and cropping sprites

	// tile stuff
	static constexpr uint8_t TILE_LEN{ 1 };
	static constexpr Vec2i TILE_DIM{ TILE_LEN * S_LEN, TILE_LEN * S_LEN };

	static constexpr Vec2i TILE_BASE_BOUNDS{ 3, 3 };
	static constexpr Vec2i TILE_FEATURE_BOUNDS{ 2, 2 };

	// player stuff
	static constexpr Vec2i PLAYER_BOUNDS{ 1, 3 };

	// TODO figure out trees

	inline static constexpr Sprite SPRITES[]
	{	//	x,				 y					w,				h,				bounds						SpriteIDs:
		{	{ 8 * S_LEN,	 0  * S_LEN },		{ 2 * S_LEN,	2 * S_LEN },	{ 1, 1 }				},	// 0 Sprite
		{	{ 0 * S_LEN,	 4  * S_LEN },		TILE_DIM,						TILE_BASE_BOUNDS		},	// 1 GroundTileBaseStart
		{	{ 4 * S_LEN,	 9  * S_LEN },		TILE_DIM,						TILE_FEATURE_BOUNDS		},	// 2 FlowerTileFeatureStart
		{	{ 6 * S_LEN,	 12 * S_LEN },		{ 2 * S_LEN,	2 * S_LEN },	{ 1, 1 }				},	// 3 TreeTileFeature
		{	{ 0 * S_LEN,	 0  * S_LEN },		{ 2 * S_LEN,	2 * S_LEN },	PLAYER_BOUNDS			},	// 4 Player
		{	{ 0 * S_LEN,	 7  * S_LEN },		TILE_DIM,						TILE_FEATURE_BOUNDS		},	// 5 GroundTileBaseFeature
	};

	static constexpr uint16_t NUM_SPRITES{ sizeof(SPRITES) / sizeof(Sprite) };

	static constexpr Vec2i TILE_CENTER_OFFSET{ 1,  1 };	// topleft tile base sprite to center  tile base sprite

public:
	// used primarily in renderer to access Sprite members
	static constexpr Sprite getSprite(const SpriteID s)
	{
		return SPRITES[static_cast<int>(s)];
	}

	// misc util sprite methods
	static constexpr Vec2i getSpriteDimensions(const SpriteID id)
	{
		return getSprite(id).dim;
	}
	static constexpr Vec2i getSpriteCoords(const SpriteID id)
	{
		return getSprite(id).pos;
	}

	// tile related methods
	static constexpr int getTileLength()			{ return TILE_LEN;			 }
	static constexpr Vec2i getTileCenterOffset()	{ return TILE_CENTER_OFFSET; }

};