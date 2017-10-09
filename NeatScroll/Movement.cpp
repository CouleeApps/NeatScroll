#include "stdafx.h"
#include "Movement.h"

Movement::Movement() {

}

Movement::~Movement() {

}

std::vector<glm::lvec3> Movement::getDeltas() const {
	std::vector<glm::lvec3> deltas;
	for (int i = 0; i < mPointCount; i++) {
		deltas.push_back(mPoints[i].origin - mStartPoints[i].origin);
	}
	return deltas;
}