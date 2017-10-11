#pragma once
#include "../Gesture.hpp"

class TaskViewClosePerformer : public Gesture::Performer {
	virtual bool onGestureStart(const Movement &movement) override;
	virtual bool onGestureMove(const Movement &movement) override;
	virtual bool onGestureStop(const Movement &movement) override;
};

