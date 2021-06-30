#include "Game.h"

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
	this->renderer.testPalette();

	//this->renderer.putPixel(2, Color{ 3, 4, 5 });

	while (this->isRunning)
	{
		this->window.update();
		
		if (this->window.isFocused())
		{
			window.render(renderer.getBuffer());
		}

		this->delta.wait(this->frameRate);
	}
}