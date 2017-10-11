#pragma once
#include "../Gesture.hpp"

class TaskViewClosePerformer : public Gesture::Performer {
	bool onGestureStart(const Movement &movement) override;
	bool onGestureMove(const Movement &movement) override;
	bool onGestureStop(const Movement &movement) override;
};

