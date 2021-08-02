#include "DeltaTime.h"

#include <SFML/System/Sleep.hpp>

void DeltaTime::start()
{
	this->clock.restart();
}

void DeltaTime::stop()
{
	this->processingTime = clock.getElapsedTime().asSeconds();
	this->totalTime += processingTime;
}

void DeltaTime::wait(const uint8_t frameRate)
{
	stop();

	const double sleepTime{ (1.f / frameRate) - processingTime };

	sf::sleep(sf::seconds(sleepTime));

	this->deltaTime = clock.getElapsedTime().asSeconds();	// total time (use this for dt calculations)

	// should add an option for whether stop() increases totalTime or not
	//this->totalTime += sleepTime;
}