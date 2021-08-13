#include "Game.h"

#include "gfx/color/ColorPalette.h"

#include <iostream>
#include "entity/Entity.h"
Game::Game(
	const uint16_t width,
	const uint16_t height,
	const uint8_t frameRate,
	const std::string& name,
	const int windowStyle)
	:
	window{ width, height, name, windowStyle },
	renderer{ width, height },
	level{ Vec2i{ width, height } },
	keyboard{ window.getWindow() },
	frameRate{ frameRate },
	isRunning{ false }
{}

void Game::loop()
{
	DeltaTime levelRenderTimer;
	DeltaTime levelUpdateTimer;

	Entity e{ SpriteSheet::getAnimatedSpriteData(AnimatedSpriteID::Player) };

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
					e.move({ 0,-1 });
				if (keyboard.a.isDown())
					e.move({ -1,0 });
				if (keyboard.s.isDown())
					e.move({ 0,1 });
				if (keyboard.d.isDown())
					e.move({ 1,0 });


				// update
				
				//levelUpdateTimer.start();
				this->level.update(delta.getDT(), renderer.getCamera());
				//levelUpdateTimer.stop();
				//std::cout << "level update: " << levelUpdateTimer.getPT() << '\n';

				e.update(delta.getDT());
				renderer.getCamera().centerOn(e.getCenterPos());
	
				// render
				//renderer.testPalette();

				//levelRenderTimer.start();
				renderer.render(this->sheet, this->level);
				//levelRenderTimer.stop();
				//std::cout << "level render: " << levelRenderTimer.getPT() << '\n';

				renderer.render(this->sheet, e);

				renderer.render(this->sheet, SpriteID::Sprite, Vec2i{69, 69}, ColorPalette(renderer, 224, true));

				window.render(renderer.getBuffer());
			}
		}
		else
			stop();

		std::cout << delta.getFPS() << '\n';

		delta.wait(this->frameRate);
	}
}