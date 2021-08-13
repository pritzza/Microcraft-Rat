#include "Camera.h"

#include "Renderer.h"
#include "sprite/Sprite.h"

#include "../util/AABB.h"

Camera::Camera(const Renderer& renderer)
	:
	renderer{ renderer }
{}

void Camera::centerOn(const Vec2i& point)
{
	this->pos = point - Vec2i{ renderer.getBufferWidth(), renderer.getBufferHeight() } / 2;
}

const bool Camera::isInView(const Sprite& s) const
{
	return this->isInView( AABB{ s.x, s.y, s.w, s.h } );
}

const bool Camera::isInView(const AABB& s) const
{
	const int rw{ renderer.getBufferWidth() / 2 };
	const int rh{ renderer.getBufferHeight() / 2 };

	const AABB fieldOfView{ pos.x - rw, pos.y - rh, pos.x + rw, pos.y + rh };

	return AABB::collide(fieldOfView, s);
}

const Vec2i Camera::getDimensions() const
{
	return Vec2i{ this->renderer.getBufferWidth(), this->renderer.getBufferHeight() };
}
