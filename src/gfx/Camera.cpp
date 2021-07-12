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
	this->pos = point;
}

const bool Camera::isInView(const Sprite& s) const
{
	const int rw{ renderer.getBufferWidth() / 2 };
	const int rh{ renderer.getBufferHeight() / 2 };
	
	const AABB fieldOfView{ pos.x - rw, pos.y - rh, pos.x + rw, pos.y + rh };
	const AABB sprite{ s.x, s.y, s.w, s.h };
	
	return AABB::collide(fieldOfView, sprite);
}
