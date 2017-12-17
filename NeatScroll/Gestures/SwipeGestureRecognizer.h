//
// Created by glennsmith on 12/17/2017.
//

#ifndef NEATSCROLL_SWIPEGESTURE_H
#define NEATSCROLL_SWIPEGESTURE_H

#include <Gesture.hpp>

enum SwipeDirection {
	Up,
	Left,
	Down,
	Right
};

template<SwipeDirection direction, int fingerCount>
class SwipeGestureRecognizer : public Gesture::Recognizer {
	float mTheshold;
public:
	explicit SwipeGestureRecognizer(float threshold) : mTheshold(threshold) {}

	bool onMovementStart(const Movement &movement) override;
	bool onMovementMove(const Movement &movement) override;
	bool onMovementStop(const Movement &movement) override;
};

template<SwipeDirection direction>
bool checkDelta(const Movement &movement, const float &threshold);

template<>
bool checkDelta<Up>(const Movement &movement, const float &threshold) {
	//See if all fingers on the gesture moved up by ~2/10 the scale
	return movement.getAverageRelativeDelta().y > threshold;
}
template<>
bool checkDelta<Left>(const Movement &movement, const float &threshold) {
	return movement.getAverageRelativeDelta().x < -threshold;
}
template<>
bool checkDelta<Down>(const Movement &movement, const float &threshold) {
	return movement.getAverageRelativeDelta().y < -threshold;
}
template<>
bool checkDelta<Right>(const Movement &movement, const float &threshold) {
	return movement.getAverageRelativeDelta().x > threshold;
}

template<SwipeDirection direction, int fingerCount>
bool SwipeGestureRecognizer<direction, fingerCount>::onMovementStart(const Movement &movement) {
	return false;
}

template<SwipeDirection direction, int fingerCount>
bool SwipeGestureRecognizer<direction, fingerCount>::onMovementMove(const Movement &movement) {
	if (movement.mPointCount != fingerCount) {
		return false;
	}

	return checkDelta<direction>(movement, mTheshold);
}

template<SwipeDirection direction, int fingerCount>
bool SwipeGestureRecognizer<direction, fingerCount>::onMovementStop(const Movement &movement) {
	return onMovementMove(movement);
}


#endif //NEATSCROLL_SWIPEGESTURE_H
