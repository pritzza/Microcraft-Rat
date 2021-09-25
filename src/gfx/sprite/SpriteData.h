#pragma once

#include <memory>

// instead of storing all sprite data in one giant 2d array
// it may be more cache friendly to separate each sprite's data seperately
// TODO; still gotta implement this
struct SpriteData
{
	const int w, h;

	const int spriteDataSize;
	const std::unique_ptr<uint8_t[]> spriteData;

	SpriteData(int x, int y, int w, int h)
		:
		w{w},
		h{h},
		spriteDataSize{ w * h },
		spriteData{ std::make_unique<uint8_t[]>(spriteDataSize) }
	{}

};