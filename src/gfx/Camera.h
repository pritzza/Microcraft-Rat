#pragma once

#include "../util/Vector.h"

class Renderer;
struct Sprite;

class Camera
{
private:
	Vec2i pos{ 0,0 };

	const Renderer& renderer;

public:
	Camera(const Renderer& renderer);

	void centerOn(const Vec2i& point);
	void centerOn(const Vec2i& point, const Vec2i& minPos, const Vec2i& maxPos);

	const bool isInView(const Sprite& s) const;

	inline const Vec2i& getPos() const { return this->pos; }

};