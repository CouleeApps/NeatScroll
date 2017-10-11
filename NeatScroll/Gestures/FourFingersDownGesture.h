#pragma once
#include "../Gesture.hpp"

class FourFingersDownGestureRecognizer : public Gesture::Recognizer {
public:
	virtual bool onMovementStart(const Movement &movement) override;
	virtual bool onMovementMove(const Movement &movement) override;
	virtual bool onMovementStop(const Movement &movement) override;
};

