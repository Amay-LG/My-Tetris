/*****************************************************************************************
* File: Timer.cpp
* Desc: Timer object for handling framerate
* 
* Author - Amay Lokesh Galappa
*
*****************************************************************************************/
#include "Timer.h"


Timer * Timer::sInstance = NULL;
/*
======================================
Initialize a Timer Instance
======================================
*/
Timer * Timer::Instance() {

    if(sInstance == NULL){
        sInstance = new Timer();
    }

    return sInstance;
}

/*
======================================
Release a Timer Instance
======================================
*/
void Timer::Release() {

    delete sInstance;
    sInstance = NULL;
}

/*
======================================
Constructor for Timer
======================================
*/
Timer::Timer() {
    Reset();
    mTimeScale = 1.0f;
}

/*
======================================
Destructor for Timer
======================================
*/
Timer::~Timer() {

}
/*
======================================
Resets Timer values
======================================
*/
void Timer::Reset() {
    mStartTicks = SDL_GetTicks();
    mElapsedTicks = 0;
    mDeltaTime = 0.0f;
}
/*
======================================
Returns the time elapsed in seconds
======================================
*/
float Timer::DeltaTime() {
    return mDeltaTime;
}

/*
======================================
Setter method for mTimeScale

mTimeScale is used to handle time-based movement
mTimeScale can be used to update game speed in future iterations

Parameters:
>> t: value to set to mTimeScale
======================================
*/
void Timer::TimeScale(float t) {
    mTimeScale = t;
}
/*
======================================
Getter method for mTimeScale
======================================
*/
float Timer::TimeScale() {
    return mTimeScale;
}

/*
======================================
Update Timer, store time elapsed in ticks in mElapsedTicks
store time elapsed in seconds in mDeltaTime
======================================
*/
void Timer::Update() {
    mElapsedTicks = SDL_GetTicks() - mStartTicks;
    mDeltaTime = mElapsedTicks * 0.001f; //Converts Ticks(ms) to seconds
}

