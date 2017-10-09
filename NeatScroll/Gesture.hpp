#pragma once
#include "Movement.h"

class Gesture {
public:
	class Recognizer {
	public:
		virtual bool onMovementStart(const Movement &movement) = 0;
		virtual bool onMovementMove(const Movement &movement) = 0;
		virtual bool onMovementStop(const Movement &movement) = 0;
	};

	class Performer {
	public:
		virtual void onGestureStart(const Movement &movement) = 0;
		virtual void onGestureMove(const Movement &movement) = 0;
		virtual void onGestureStop(const Movement &movement) = 0;
	};

	Gesture(Recognizer &recognizer, Performer &performer);

	bool onMovementStart(const Movement &movement) { return mRecognizer.onMovementStart(movement); }
	bool onMovementMove(const Movement &movement) { return mRecognizer.onMovementMove(movement); }
	bool onMovementStop(const Movement &movement) { return mRecognizer.onMovementStop(movement); }
	void onGestureStart(const Movement &movement) { return mPerformer.onGestureStart(movement); }
	void onGestureMove(const Movement &movement) { return mPerformer.onGestureMove(movement); }
	void onGestureStop(const Movement &movement) { return mPerformer.onGestureStop(movement); }

protected:
	Recognizer &mRecognizer;
	Performer &mPerformer;
};
