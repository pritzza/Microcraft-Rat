#include "Game.h"

#include "gfx/color/ColorPalette.h"

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
	uint8_t x{};

	this->level.generateWorld();

	while (isRunning)
	{
		window.update();
		
		if (window.isOpen())
		{
			if (window.isFocused())
			{
				//renderer.getCamera().centerOn(Vec2i{ x, 0 });
				renderer.testPalette();
				renderer.render(this->sheet, SpriteSheet::SpriteID::Sprite, Vec2i{69, 69}, ColorPalette(renderer, 224, true));
				renderer.putPixel( Vec2i{ x, 0 }, Color{ 0, 0, 0 });

				renderer.render(this->sheet, this->level);

				++x;

				window.render(renderer.getBuffer());
			}
		}
		else
			stop();

		delta.wait(frameRate);
	}
}