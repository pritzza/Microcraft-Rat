#pragma once

#include "Button.h"

namespace sf { class RenderWindow; }

class Keyboard
{
private:
	const sf::RenderWindow& window;

public:
	Button w, a, s, d, e, space;

public:
	Keyboard(const sf::RenderWindow& window);

	void update();
};