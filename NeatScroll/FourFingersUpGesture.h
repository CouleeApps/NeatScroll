#pragma once
#include "Gesture.hpp"

class FourFingersUpGestureRecognizer : public Gesture::Recognizer {
public:
	virtual bool onMovementStart(const Movement &movement) override;
	virtual bool onMovementMove(const Movement &movement) override;
	virtual bool onMovementStop(const Movement &movement) override;
};

class FourFingersUpGesturePerformer : public Gesture::Performer {
	virtual bool onGestureStart(const Movement &movement) override;
	virtual bool onGestureMove(const Movement &movement) override;
	virtual bool onGestureStop(const Movement &movement) override;
};

