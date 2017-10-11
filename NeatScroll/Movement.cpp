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

std::vector<glm::vec3> Movement::getRelativeDeltas() const {
	std::vector<glm::vec3> deltas;
	for (int i = 0; i < mPointCount; i++) {
		glm::lvec3 scale = mPoints[0].scale;
		glm::vec3 delta = glm::vec3(mPoints[i].origin - mStartPoints[i].origin);
		delta.x /= scale.x / (float)mPointCount;
		delta.y /= scale.y / (float)mPointCount;
		delta.z /= scale.z / (float)mPointCount;
		deltas.push_back(delta);
	}
	return deltas;
}

glm::vec3 Movement::getAverageDelta() const {
	glm::vec3 avgDelta;
	for (int i = 0; i < mPointCount; i++) {
		glm::vec3 delta = glm::vec3(mPoints[i].origin - mStartPoints[i].origin);
		avgDelta.x += delta.x / (float)mPointCount;
		avgDelta.y += delta.y / (float)mPointCount;
		avgDelta.z += delta.z / (float)mPointCount;
	}

	return avgDelta;
}

glm::vec3 Movement::getAverageRelativeDelta() const {
	glm::vec3 avgDelta;
	for (int i = 0; i < mPointCount; i++) {
		glm::lvec3 scale = mPoints[i].scale;
		glm::vec3 delta = glm::vec3(mPoints[i].origin - mStartPoints[i].origin);
		avgDelta.x += delta.x / scale.x / (float)mPointCount;
		avgDelta.y += delta.y / scale.y / (float)mPointCount;
		avgDelta.z += delta.z / scale.z / (float)mPointCount;
	}

	return avgDelta;
}

