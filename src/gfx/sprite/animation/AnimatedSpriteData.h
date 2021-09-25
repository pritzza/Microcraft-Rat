#pragma once

enum class AnimationType;
enum class SpriteID;

struct AnimatedSpriteData
{
public:
	const AnimationType animationType{};
	const SpriteID spriteID{};
	const double frameDuration{};

private:
	constexpr AnimatedSpriteData(const AnimationType type, const SpriteID id, const double frameDuration)
		:
		animationType{ type },
		spriteID{ id },
		frameDuration{ frameDuration }
	{}

	friend class SpriteSheetAnimationData;
};