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
};

