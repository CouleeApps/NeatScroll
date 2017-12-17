//
// Created by glennsmith on 12/17/2017.
//

#ifndef NEATSCROLL_CONDITIONALPERFORMER_H
#define NEATSCROLL_CONDITIONALPERFORMER_H

#include "Gesture.hpp"
#include <functional>

class ConditionalPerformer : public Gesture::Performer {
	Gesture::Performer &mPerformer;
	std::function<bool(void)> mConditionFn;
public:
	ConditionalPerformer(Gesture::Performer &performer, const std::function<bool(void)> &conditionFn) : mPerformer(performer), mConditionFn(conditionFn) {}

	bool onGestureStart(const Movement &movement) override;
	bool onGestureMove(const Movement &movement) override;
	bool onGestureStop(const Movement &movement) override;
};

bool ConditionalPerformer::onGestureStart(const Movement &movement) {
	if (!mConditionFn()) {
		return false;
	}
	return mPerformer.onGestureStart(movement);
}

bool ConditionalPerformer::onGestureMove(const Movement &movement) {
	if (!mConditionFn()) {
		return false;
	}
	return mPerformer.onGestureMove(movement);
}

bool ConditionalPerformer::onGestureStop(const Movement &movement) {
	if (!mConditionFn()) {
		return false;
	}
	return mPerformer.onGestureStop(movement);
}

#endif //NEATSCROLL_CONDITIONALPERFORMER_H
