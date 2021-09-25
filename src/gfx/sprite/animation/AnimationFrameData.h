#pragma once

#include "../../../util/Direction.h"

enum class RenderFlag;

struct KeyFrameData
{
	const int index;
	const RenderFlag transformation;
};

class AnimationFrameData final
{
private:
	const std::vector<KeyFrameData> animations[Directions::NUM_DIRECTIONS];

public:
	AnimationFrameData(
		const std::initializer_list<KeyFrameData> north,
		const std::initializer_list<KeyFrameData> south,
		const std::initializer_list<KeyFrameData> east,
		const std::initializer_list<KeyFrameData> west
	)
		:
		animations{ north, south, east, west }
	{}

	const std::vector<KeyFrameData>& getAnimation(const Direction d) const	{ return animations[static_cast<int>(d)];	}
	const int getNumFrames(const Direction d) const							{ return getAnimation(d).size();			}
};