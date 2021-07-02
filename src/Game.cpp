#include "Game.h"

#include "gfx/ColorPalette.h"

#include <iostream>

Game::Game(
	const uint16_t width, 
	const uint16_t height, 
	const uint8_t frameRate, 
	const std::string& name,
	const int windowStyle)
	:
	window{ width, height, name, windowStyle },
	renderer{ width, height },
	frameRate{ frameRate },
	isRunning{ false }
{}

void Game::loop()
{
	renderer.testPalette();

	renderer.render(this->sheet, SpriteSheet::SpriteID::Sprite, { 35, 70, 80, 123 }, 1, 1);

	while (isRunning)
	{
		window.update();
		
		if (!window.isOpen())
			stop();

		else if (window.isFocused())
		{
			window.render(renderer.getBuffer());
		}

		delta.wait(frameRate);
	}
}