#pragma once

#include <SFML/Window/WindowStyle.hpp>

#include "gfx/Renderer.h"

#include "util/DeltaTime.h"
#include "util/Window.h"

class Game
{
private:
	Window window;
	Renderer renderer;
	DeltaTime delta;

	const uint8_t frameRate;
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

	inline void start() { this-> isRunning = true; this->loop(); }

};