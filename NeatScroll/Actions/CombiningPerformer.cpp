//
// Created by glennsmith on 12/17/2017.
//

#include "stdafx.h"
#include "CombiningPerformer.h"

bool CombiningPerformer::onGestureStart(const Movement &movement) {
	for (auto performer : mPerformers) {
		if (!performer->onGestureStart(movement)) {
			return false;
		}
	}
	return true;
}

bool CombiningPerformer::onGestureMove(const Movement &movement) {
	for (auto performer : mPerformers) {
		if (!performer->onGestureMove(movement)) {
			return false;
		}
	}
	return true;
}

bool CombiningPerformer::onGestureStop(const Movement &movement) {
	for (auto performer : mPerformers) {
		if (!performer->onGestureStop(movement)) {
			return false;
		}
	}
	return true;
}
