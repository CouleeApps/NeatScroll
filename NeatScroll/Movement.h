#pragma once

#include <vector>
#include "Touchpad.hpp"

struct Movement {
public:
	Movement();
	~Movement();

	int mPointCount;
	std::vector<Touchpad::TouchPoint> mPoints;
	std::vector<Touchpad::TouchPoint> mStartPoints;

	std::vector<glm::lvec3> getDeltas() const;
	std::vector<glm::vec3> getRelativeDeltas() const;
	glm::vec3 getAverageDelta() const;
	glm::vec3 getAverageRelativeDelta() const;
};

