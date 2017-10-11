#pragma once
#include "../Gesture.hpp"

class FourFingersRightGestureRecognizer : public Gesture::Recognizer {
public:
	bool onMovementStart(const Movement &movement) override;
	bool onMovementMove(const Movement &movement) override;
	bool onMovementStop(const Movement &movement) override;
};
