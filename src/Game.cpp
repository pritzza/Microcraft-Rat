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
	level{ Vec2i{width, height} },
	keyboard{ window.getWindow() },
	frameRate{ frameRate },
	isRunning{ false }
{}

void Game::loop()
{
	Vec2i cameraCenter{ 0,0 };
	DeltaTime timer;

	while (isRunning)
	{
		window.update();
		delta.start();

		if (window.isOpen())
		{
			keyboard.update();

			if (window.isFocused())
			{
				// handle input
				if (keyboard.w.isDown())
					cameraCenter.y--;
				if (keyboard.a.isDown())
					cameraCenter.x--;
				if (keyboard.s.isDown())
					cameraCenter.y++;
				if (keyboard.d.isDown())
					cameraCenter.x++;

				renderer.getCamera().centerOn(cameraCenter);

				// update
				
				this->level.update(renderer.getCamera());

				//camPos.print();
				//centerChunk.print();

				// render
				renderer.testPalette();

				timer.start();
				renderer.render(this->sheet, this->level);
				timer.stop();
				//std::cout << timer.getPT() << '\n';

				renderer.render(this->sheet, SpriteSheet::SpriteID::Sprite, Vec2i{69, 69}, ColorPalette(renderer, 224, true));

				window.render(renderer.getBuffer());
			}
		}
		else
			stop();

		std::cout << delta.getFPS() << '\n';

		delta.wait(this->frameRate);
	}
}