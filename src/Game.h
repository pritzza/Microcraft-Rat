#pragma once

#include <SFML/Window/WindowStyle.hpp>

#include "gfx/Renderer.h"
#include "gfx/sheet/SpriteSheet.h"

#include "util/DeltaTime.h"
#include "util/Window.h"

#include "level/Level.h"

#include "input/Keyboard.h"

class Game
{
private:
	Window window;
	Renderer renderer;
	SpriteSheet sheet{"res/SpriteSheet.png"};

	DeltaTime delta;

	Keyboard keyboard;

	Level level;

	uint8_t frameRate;
	bool isRunning;

private:
	void loop();

	inline void stop() { this->isRunning = false; }

public:
	Game(
		const uint16_t width,
		const uint16_t height,
		const uint8_t frameRate,
		const std::string& name,
		const int windowStyle
	);

	inline void start() 
	{
		this->isRunning = true; 
		this->loop();
	}

};