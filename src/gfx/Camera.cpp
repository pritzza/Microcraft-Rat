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
	return this->isInView( AABB{ s.pos.x, s.pos.y, s.dim.x, s.dim.y } );
}

const bool Camera::isInView(const AABB& s) const
{
	const int rw{ renderer.getBufferWidth()  };
	const int rh{ renderer.getBufferHeight() };

	const AABB fieldOfView{ pos.x, pos.y, rw, rh };

	return AABB::collide(s, fieldOfView);
}

const Vec2i Camera::getDimensions() const
{
	return Vec2i{ this->renderer.getBufferWidth(), this->renderer.getBufferHeight() };
}
