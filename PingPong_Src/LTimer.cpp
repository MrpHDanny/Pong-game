#include "LTimer.h"


LTimer::LTimer()
{
	startTicks = 0;
	pausedTicks = 0;

	isPaused_ = false;
	isStarted_ = false;
}

void LTimer::start()
{
	isStarted_ = true;
	isPaused_ = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void LTimer::stop()
{
	isStarted_ = false;
	isPaused_ = false;

	startTicks = 0;
	pausedTicks = 0;
}

void LTimer::pause()
{
	if ( !isPaused_ && isStarted_ )
	{
		isPaused_ = true;

		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}


void LTimer::unpause()
{
	if ( !isStarted_ && isPaused_ )
	{
		isPaused_ = false;

		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}

}

Uint32 LTimer::getTicks()
{
	Uint32 time = 0;

	if ( isStarted_ )
	{
		if (isPaused_ )
		{
			return pausedTicks;
		}

		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

bool LTimer::isStarted()
{
	return isStarted_;
}

bool LTimer::isPaused()
{
	return isPaused_ && isStarted_;
}