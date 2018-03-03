#include "stdafx.h"
#include "Movement.h"

std::vector<glm::lvec3> Movement::getDeltas(const std::vector<Touchpad::TouchPoint> &start,
        const std::vector<Touchpad::TouchPoint> &end) {
	std::vector<glm::lvec3> deltas;
	for (int i = 0; i < start.size(); i++) {
		deltas.push_back(end[i].origin - start[i].origin);
	}
	return deltas;
}

std::vector<glm::vec3> Movement::getRelativeDeltas(const std::vector<Touchpad::TouchPoint> &start,
        const std::vector<Touchpad::TouchPoint> &end) {
	std::vector<glm::vec3> deltas;
	for (int i = 0; i < start.size(); i++) {
		glm::lvec3 scale = end[0].scale;
		glm::vec3 delta = glm::vec3(end[i].origin - start[i].origin);
		delta.x /= scale.x / (float)start.size();
		delta.y /= scale.y / (float)start.size();
		delta.z /= scale.z / (float)start.size();
		deltas.push_back(delta);
	}
	return deltas;
}

glm::vec3 Movement::getAverageDelta(const std::vector<Touchpad::TouchPoint> &start,
        const std::vector<Touchpad::TouchPoint> &end) {
	glm::vec3 avgDelta;
	for (int i = 0; i < start.size(); i++) {
		glm::vec3 delta = glm::vec3(end[i].origin - start[i].origin);
		avgDelta.x += delta.x / (float)start.size();
		avgDelta.y += delta.y / (float)start.size();
		avgDelta.z += delta.z / (float)start.size();
	}

	return avgDelta;
}

glm::vec3 Movement::getAverageRelativeDelta(const std::vector<Touchpad::TouchPoint> &start,
        const std::vector<Touchpad::TouchPoint> &end) {
	glm::vec3 avgDelta;
	for (int i = 0; i < start.size(); i++) {
		glm::lvec3 scale = end[i].scale;
		glm::vec3 delta = glm::vec3(end[i].origin - start[i].origin);
		avgDelta.x += delta.x / scale.x / (float)start.size();
		avgDelta.y += delta.y / scale.y / (float)start.size();
		avgDelta.z += delta.z / scale.z / (float)start.size();
	}

	return avgDelta;
}
