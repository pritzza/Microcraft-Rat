#pragma once

#include "Button.h"

#include "../util/Vector.h"

namespace sf { class Window; }

class Mouse
{
private:
	sf::Window& window;

public:
	Button lclick, rclick, mclick;

public:
	Mouse(sf::Window& window);

	void update();

	const Vec2i getPos() const;
};