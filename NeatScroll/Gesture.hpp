#pragma once
#include "Movement.hpp"

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
		virtual bool onGestureStart(const Movement &movement) = 0;
		virtual bool onGestureMove(const Movement &movement) = 0;
		virtual bool onGestureStop(const Movement &movement) = 0;
	};

	Gesture(Recognizer &recognizer, Performer &performer);

	bool onMovementStart(const Movement &movement) { return mRecognizer.onMovementStart(movement); }
	bool onMovementMove(const Movement &movement) { return mRecognizer.onMovementMove(movement); }
	bool onMovementStop(const Movement &movement) { return mRecognizer.onMovementStop(movement); }
	bool onGestureStart(const Movement &movement) { return mPerformer.onGestureStart(movement); }
	bool onGestureMove(const Movement &movement) { return mPerformer.onGestureMove(movement); }
	bool onGestureStop(const Movement &movement) { return mPerformer.onGestureStop(movement); }

protected:
	Recognizer &mRecognizer;
	Performer &mPerformer;
};
