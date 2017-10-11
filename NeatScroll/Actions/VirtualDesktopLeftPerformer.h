#pragma once
#include "../Gesture.hpp"

class VirtualDesktopLeftPerformer : public Gesture::Performer {
	bool onGestureStart(const Movement &movement) override;
	bool onGestureMove(const Movement &movement) override;
	bool onGestureStop(const Movement &movement) override;
};
