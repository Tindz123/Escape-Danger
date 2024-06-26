#include "timer.h"


LTimer::LTimer()
{
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}
void LTimer::start()
{
    mStarted = true;
    mPaused = false;

    mStartTicks = SDL_GetTicks();
}
void LTimer::stop()
{
    mStarted = false;
    mPaused = false;

}
void LTimer::pause()
{
    if( mStarted == true && mPaused == false)
    {
        mPaused = true;

        mPausedTicks = SDL_GetTicks() - mStartTicks;
    }
}
void LTimer::unpause()
{
    if( mPaused )
    {
        mPaused = false;
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}
int LTimer::getTicks()
{
	int time = 0;

    if( mStarted )
    {
        if( mPaused )
        {
            time = mPausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - mStartTicks;
            mStartTicks = 0;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
    return mStarted;
}

bool LTimer::isPaused()
{
    return mPaused && mStarted;
}
