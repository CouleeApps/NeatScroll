//
// Created by glennsmith on 12/23/2017.
//

#ifndef NEATSCROLL_HIGHPERFORMANCETIMER_HPP
#define NEATSCROLL_HIGHPERFORMANCETIMER_HPP

#include "Timer.hpp"
#include <Windows.h>

class HighPerformanceTimer : public Timer {
	LARGE_INTEGER mStartTime{};
public:
	void start() override;
	TickType getTickCount() const override;
	TickType getTicksPerSecond() const override;
};


#endif //NEATSCROLL_HIGHPERFORMANCETIMER_HPP
