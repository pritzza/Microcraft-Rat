#pragma once

#include <SFML/System/Clock.hpp>

#include <cstdint>

class DeltaTime final
{
private:
	sf::Clock clock;

	double deltaTime{};			// time between each frame in seconds
	double processingTime{};	// the time it takes to execute one gameloop excluding the wait/sleep

	double totalTime{};

public:
	void start();
	void stop();

	void wait(const uint8_t frameRate);

	inline const double getDT() const		{ return this->deltaTime;		 }
	inline const double getPT() const		{ return this->processingTime;   }
	inline const double getTotal() const	{ return this->totalTime;		 }
	inline const double getFPS() const		{ return (deltaTime / processingTime) * (1.f / deltaTime); }
};