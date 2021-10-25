#pragma once

#include "SpriteSheetData.h"

#include "../sprite/animation/AnimatedSprite.h"
#include "../sprite/animation/AnimationFrameData.h"

#include "../Renderer.h"

// AnimatedSpriteID gives IDs to all sprites that are meant to be animated
// make sure order here matches ANIMATED_SPRITES
enum class AnimatedSpriteID
{
	Player,						// 0

	UnAnimatedGroundTileBase,	// 1
	Water,						// 2

	EmptyTileFeature,			// 3
	StaticFlower,				// 4
	DancingFlower,				// 5
	Tree,						// 6

	NumAnimatedSpriteIDs
};

// a classifer for the frame data an animated sprite has
enum class AnimationType
{
	None,					// Not animated
	Standard,				// has 1 keyframe for north, south, and two for lateral movement
	Mono,					// doesnt care about direction, just alternates between 2 frames
	StandardTileBase,		// goes through flavors
	StandardTileFeature,	// also goes through flavors	(just different because how bases and features are organized in SH)

	NumAnimationTypes
};

class SpriteSheetAnimationData
{
private:
	inline static constexpr AnimatedSpriteData ANIMATED_SPRITES[static_cast<int>(AnimatedSpriteID::NumAnimatedSpriteIDs)]
	{
		// type of animation, actual sprite ID, frame duration								// AnimatedSpriteID s:
		{ AnimationType::Standard,				SpriteID::Player,				0.3f },	// 0 Player
		{ AnimationType::None,					SpriteID::GroundTileBase,		0.0f },	// 1 UnAnimatedTileBase
		{ AnimationType::StandardTileBase,		SpriteID::GroundTileBase,		1.0f }, // 2 Water
		{ AnimationType::None,					SpriteID::Player,				0.0f }, // 3 EmptyTileFeature
		{ AnimationType::StandardTileFeature,	SpriteID::FlowerTileFeature,	0.0f }, // 4 StaticFlower
		{ AnimationType::StandardTileFeature,	SpriteID::FlowerTileFeature,	0.2f }, // 4 DancingFlower
		{ AnimationType::None,					SpriteID::TreeTileFeature,		0.0f }, // 5 Tree
	};
	
	// lil abbreviations
	inline static constexpr Direction N{ Direction::North };
	inline static constexpr Direction S{ Direction::South };
	inline static constexpr Direction E{ Direction::East };
	inline static constexpr Direction W{ Direction::West };

	inline static constexpr RenderFlag X{ RenderFlag::FLIP_X };
	inline static constexpr RenderFlag Y{ RenderFlag::FLIP_Y };
	inline static constexpr RenderFlag B{ RenderFlag::FLIP_BOTH };
	inline static constexpr RenderFlag O{ RenderFlag::NONE };

	inline static const AnimationFrameData ANIMATION_FRAME_DATA[static_cast<int>(AnimationType::NumAnimationTypes)]
	{
		// north, south, east, west animations
		// index, transformation
		{ {{0, O}},			 {},				{},					{}					},	// 0 None

		{ {{1, O}, {1, X}},  {{0, O}, {0, X}},  {{2, O}, {3, O}},	{{2, X}, {3, X}}	},	// 1 Standard Mob

		{ {{0, O}},			 {},				{},					{}					},	// 2 Mono

		{ {{0, O}, {1, O}, {2, O}, {3, O}, {4, O}},					{},	{},	{}			},	// 3 Standard Tile Base

		{ {{0, O}, {1, O}, {2, O}, {3, O}},							{}, {}, {}			},	// 4 Standard Tile Feature

	};

public:
	static constexpr AnimatedSpriteData getAnimatedSpriteData(const AnimatedSpriteID asID)
	{
		return ANIMATED_SPRITES[static_cast<int>(asID)];
	}

	static const AnimationFrameData& getAnimationFrameData(const AnimationType aType)
	{
		return ANIMATION_FRAME_DATA[static_cast<int>(aType)];
	}

};