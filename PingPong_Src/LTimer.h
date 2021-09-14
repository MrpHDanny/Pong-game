#pragma once
#include <SDL.h>


class LTimer
{
public:
	LTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

protected:
	Uint32 startTicks;
	Uint32 pausedTicks;

	bool isPaused_;
	bool isStarted_;

};

