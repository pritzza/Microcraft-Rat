#include "DeltaTime.h"

#include <SFML/System/Sleep.hpp>

void DeltaTime::wait(const uint8_t frameRate)
{
	this->m_clock.restart();

	this->m_processingTime = m_clock.getElapsedTime().asSeconds();	// processing time before wait
	sf::sleep(sf::seconds(1.f / frameRate - m_processingTime));

	this->m_deltaTime = m_clock.getElapsedTime().asSeconds();	// total time (use this for dt calculations)
	this->m_totalTime += m_deltaTime;
}