//
// Created by glennsmith on 12/17/2017.
//

#ifndef NEATSCROLL_SWIPEGESTURE_H
#define NEATSCROLL_SWIPEGESTURE_H

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
public:
	explicit SwipeGestureRecognizer(Direction mDirection, int mFingerCount, float threshold)
			: mThreshold(threshold), mDirection(mDirection), mFingerCount(mFingerCount) {}

	bool onMovementStart(const Movement &movement) override;
	bool onMovementMove(const Movement &movement) override;
	bool onMovementStop(const Movement &movement) override;
};

#endif //NEATSCROLL_SWIPEGESTURE_H
