#pragma once

#include <SFML/System/Clock.hpp>

#include <cstdint>

class DeltaTime final
{
private:
	sf::Clock m_clock;

	double m_deltaTime{};			// time between each frame
	double m_processingTime{};	// the time it takes to execute one gameloop excluding the wait/sleep

	double m_totalTime{};

public:
	void wait(const uint8_t frameRate);

	inline const double getDT() const		{ return this->m_deltaTime;		 }
	inline const double getPT() const		{ return this->m_processingTime; }
	inline const double getTotal() const	{ return this->m_totalTime;		 }
};