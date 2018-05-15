//
// Created by glennsmith on 12/17/2017.
//

#ifndef NEATSCROLL_SWIPEGESTURE_HPP
#define NEATSCROLL_SWIPEGESTURE_HPP

#include "../Timer.hpp"
#include <vector>
#include "../Gesture.hpp"

class SwipeGestureRecognizer : public Gesture::Recognizer {
public:
	enum Direction {
		Up,
		Left,
		Down,
		Right
	};
private:
	Direction mDirection;
	int mFingerCount;
	float mThreshold;
	float mTimeout;

	std::vector<std::pair<Timer::TickType, Movement>> mHistory;

	Timer *mTimer;
public:
	explicit SwipeGestureRecognizer(Direction mDirection, int mFingerCount, float threshold,
		                                float timeout, Timer *timer)
			: mThreshold(threshold), mDirection(mDirection), mFingerCount(mFingerCount), mTimeout(timeout),
			  mTimer(timer) {}

	bool onMovementStart(const Movement &movement) override;
	bool onMovementMove(const Movement &movement) override;
	bool onMovementStop(const Movement &movement) override;
};

#endif //NEATSCROLL_SWIPEGESTURE_HPP
