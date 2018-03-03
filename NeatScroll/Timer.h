//
// Created by glennsmith on 12/23/2017.
//

#ifndef NEATSCROLL_TIMER_H
#define NEATSCROLL_TIMER_H

#include <stdint.h>

class Timer {
public:
	typedef int64_t TickType;

	virtual void start() = 0;
	virtual TickType getTickCount() const = 0;
	virtual TickType getTicksPerSecond() const = 0;
};


#endif //NEATSCROLL_TIMER_H
