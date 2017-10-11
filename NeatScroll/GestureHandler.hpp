#pragma once
#include "MovementDetector.hpp"
#include "Gesture.hpp"

class GestureHandler : public GestureDetector {
public:
	GestureHandler();
	~GestureHandler();

	void addGesture(Gesture *gesture) {
		mGestures.push_back(gesture);
	}

	void onMovementStart(const Movement &movement) override;
	void onMovementMove(const Movement &movement) override;
	void onMovementStop(const Movement &movement) override;

private:
	std::vector<Gesture *> mGestures;
	Gesture *mActiveGesture;
};