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

	virtual void onMovementStart(const Movement &movement) override;
	virtual void onMovementMove(const Movement &movement) override;
	virtual void onMovementStop(const Movement &movement) override;

private:
	std::vector<Gesture *> mGestures;
	Gesture *mActiveGesture;
};