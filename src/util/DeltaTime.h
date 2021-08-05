#pragma once

#include <SFML/System/Clock.hpp>

#include <cstdint>

class DeltaTime final
{
private:
	sf::Clock clock;

	long frame{};

	double deltaTime{};			// time between each frame in seconds
	double processingTime{};	// the time it takes to execute one gameloop excluding the wait/sleep

	double totalProcessingTime{};
	double totalTime{};

public:
	void start();
	void stop();

	void wait(const int targetFrameRate);

	inline const long   getFrame() const		{ return this->frame;			 }
	inline const double getDT() const			{ return this->deltaTime;		 }
	inline const double getPT() const			{ return this->processingTime;   }

	inline const double getTotalPT() const		{ return this->totalProcessingTime; }
	inline const double getTotalTime() const	{ return this->totalTime;		    }

	inline const double getFPS() const			{ return (deltaTime / processingTime) * (1.f / deltaTime); }
	
	// dont work
	//inline const double getAverageFPS() const	
	//{
	//	return (totalProcessingTime/frame);
	//}
};