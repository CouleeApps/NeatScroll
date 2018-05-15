//
// Created by glennsmith on 12/23/2017.
//

#include "stdafx.h"
#include "HighPerformanceTimer.hpp"


void HighPerformanceTimer::start() {
	LARGE_INTEGER time {};
	QueryPerformanceCounter(&time);

	mStartTime = time;
}

Timer::TickType HighPerformanceTimer::getTickCount() const {
	LARGE_INTEGER stopTime {};
	QueryPerformanceCounter(&stopTime);
	return static_cast<TickType>(stopTime.QuadPart - mStartTime.QuadPart);
}

Timer::TickType HighPerformanceTimer::getTicksPerSecond() const {
	LARGE_INTEGER frequency {};
	QueryPerformanceFrequency(&frequency);
	return static_cast<TickType>(frequency.QuadPart);
}
