#pragma once
#include "Gesture.hpp"

class FourFingersLeftGestureRecognizer : public Gesture::Recognizer {
public:
	virtual bool onMovementStart(const Movement &movement) override;
	virtual bool onMovementMove(const Movement &movement) override;
	virtual bool onMovementStop(const Movement &movement) override;
};

class FourFingersLeftGesturePerformer : public Gesture::Performer {
	virtual void onGestureStart(const Movement &movement) override;
	virtual void onGestureMove(const Movement &movement) override;
	virtual void onGestureStop(const Movement &movement) override;
};

