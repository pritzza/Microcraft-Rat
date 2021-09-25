#include "Game.h"

#include "gfx/color/ColorPalette.h"
#include "gfx/sheet/SpriteSheetAnimationData.h"
#include "entity/Entity.h"

#include <iostream>

Game::Game(
	const uint16_t width,
	const uint16_t height,
	const uint8_t frameRate,
	const std::string& name,
	const int windowStyle)
	:
	window{ width, height, name, windowStyle },
	renderer{ sheet, width, height },
	keyboard{ window.getWindow() },
	frameRate{ frameRate },
	isRunning{ false }
{}

void Game::loop()
{
	DeltaTime levelUpdateTimer;
	DeltaTime levelRenderTimer;

	DeltaTime entityRenderTimer;

	DeltaTime renderTimer;

	Entity e{ AnimatedSpriteID::Player, ColorPalette( -1, 333, 444, 555 ) };

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
				//std::cout << "level update: " << levelUpdateTimer.getTotalPT() / delta.getTotalPT() << '\n';

				e.update(delta.getDT());
				renderer.getCamera().centerOn(e.getCenterPos());
	
				// render
				//renderer.testPalette();

				//levelRenderTimer.start();
				renderer.render(this->level);
				//levelRenderTimer.stop();
				//std::cout << "level render: " << levelRenderTimer.getTotalPT() / delta.getTotalPT() << '\n';


				//entityRenderTimer.start();
				renderer.render(e);
				//entityRenderTimer.stop();
				//std::cout << "entity render: " << entityRenderTimer.getTotalPT() / delta.getTotalPT() << '\n';

				//renderer.render(this->sheet, SpriteID::Sprite, Vec2i{69, 69}, ColorPalette(renderer, 224, true));

				//renderTimer.start();
				renderer.renderQueue();
				//renderTimer.stop();
				//std::cout << "render: " << renderTimer.getTotalPT() / delta.getTotalPT() << '\n';

				window.render(renderer.getBuffer());
			}
		}
		else
			stop();

		std::cout << "\rFPS: " << delta.getFPS() << ", " << delta.getTotalPT() / delta.getTotalTime() << '\n';

		delta.wait(this->frameRate);
	}
}