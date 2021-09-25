#pragma once

#include "../../util/Vector.h"

class Tile;
struct TileFeatureData;

class World;

struct AnimatedSprite;

// by "offset", i mean the displacement vector (in pixels) between the start of a series sprite keyframes
// and where a specific frame in the sprites animation is (in the sprite sheet)
// 
// eg: if some sprite's animations start at 0,0 in the sprite sheet, and we want the 
// second frame from the origin, we would have an offset of (SPRITE_W * 2, 0)
// 
// these offsets can and will arbitrary vary between different type of sprites like tile bases, features, 
//large features, entities, etc according to how i decide to organize the spritesheet

// graphics utility class meant to take in a Sprite class, and return a vector offset for where the sprite
// begins in the spritesheet to effectivly crop out animation or variant sprites
class SpriteCropper final
{
public:
	const Vec2i getTileBaseOffset(const Tile& tile, const int compIndex, const World& world, const Vec2i& chunkCoords, const int tileIndex) const;
	const Vec2i getTileFeatureOffset(const Tile& tile, const int compIndex, const int featureSpriteLen) const;

	//const Vec2i getAnimationFrameOffset(const AnimatedSprite& animatedSprite) const;

};