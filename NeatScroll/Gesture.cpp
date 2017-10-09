#include "stdafx.h"
#include "Gesture.h"

Gesture::Gesture() {

}

Gesture::~Gesture() {

}

std::vector<glm::lvec3> Gesture::getDeltas() const {
	std::vector<glm::lvec3> deltas;
	for (int i = 0; i < mPointCount; i++) {
		deltas.push_back(mPoints[i].origin - mStartPoints[i].origin);
	}
	return deltas;
}