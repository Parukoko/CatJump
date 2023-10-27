#pragma once
#include <SFML/Graphics.hpp>
class Timer
{
public :
	Timer();
	void Start();
	void Stop();
	void Reset();
	float GetTotalTime();
private :
	sf::Clock clock;
	bool isRunning;
	float totalTime;
};

