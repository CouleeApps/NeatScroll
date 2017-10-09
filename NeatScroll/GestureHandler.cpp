#include "stdafx.h"
#include "GestureHandler.hpp"

GestureHandler::GestureHandler() {

}

GestureHandler::~GestureHandler() {

}

void GestureHandler::onMovementStart(const Movement &movement) {
	mActiveGesture = nullptr;

	//See if we get a gesture recognized
	for (const auto &gesture : mGestures) {
		if (gesture->onMovementStop(movement)) {
			//Right at the start? That was quick
			mActiveGesture = gesture;
			gesture->onGestureStart(movement);
			break;
		}
	}
}

void GestureHandler::onMovementMove(const Movement &movement) {
	//See if we get a gesture recognized
	if (mActiveGesture == nullptr) {
		for (const auto &gesture : mGestures) {
			if (gesture->onMovementStop(movement)) {
				//That recognizer got something, use it
				mActiveGesture = gesture;
				gesture->onGestureStart(movement);
				break;
			}
		}
	}

	//Tell our active recognizer to update
	if (mActiveGesture) {
		mActiveGesture->onGestureMove(movement);
	}
}

void GestureHandler::onMovementStop(const Movement &movement) {
	//See if we finally get a gesture recognized at the end
	if (mActiveGesture == nullptr) {
		for (const auto &gesture : mGestures) {
			if (gesture->onMovementStop(movement)) {
				//That recognizer got something, use it
				mActiveGesture = gesture;
				gesture->onGestureStart(movement);
				break;
			}
		}
	}

	//Tell our active recognizer that we're done
	if (mActiveGesture) {
		mActiveGesture->onGestureStop(movement);
	}

	mActiveGesture = nullptr;
}
