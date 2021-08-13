#pragma once

enum class SpriteID;

enum class AnimationType
{
	Standard,	// has 1 keyframe for north, south, and two for lateral movement
	Mono,		// doesnt care about direction, just alternates between 2 frames
	Tile,		// goes through tile flavors
};

struct AnimatedSpriteData
{
public:
	const AnimationType animationType{};
	const SpriteID spriteID{};
	const double frameDuration{};

private:
	constexpr AnimatedSpriteData(const AnimationType type, const SpriteID id, const float frameDuration)
		:
		animationType{ type },
		spriteID{ id },
		frameDuration{ frameDuration }
	{}

	friend class SpriteSheet;
};