#include "DeltaTime.h"

#include <SFML/System/Sleep.hpp>

void DeltaTime::start()
{
	this->clock.restart();
}

void DeltaTime::stop()
{
	this->processingTime = clock.getElapsedTime().asSeconds();
	this->totalProcessingTime += processingTime;
}

void DeltaTime::wait(const int targetFrameRate)
{
	this->frame++;
	
	stop();

	const double sleepTime{ (1.f / targetFrameRate) - processingTime };
	
	sf::sleep(sf::seconds(sleepTime));

	this->deltaTime = clock.getElapsedTime().asSeconds();	// total time (use this for dt calculations)

	this->totalTime += deltaTime;
}