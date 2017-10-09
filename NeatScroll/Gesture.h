#pragma once

#include <vector>
#include "Touchpad.hpp"

struct Gesture {
public:
	Gesture();
	~Gesture();

	int mPointCount;
	bool mMetThreshold;
	std::vector<Touchpad::TouchPoint> mPoints;
	std::vector<Touchpad::TouchPoint> mStartPoints;

	std::vector<glm::lvec3> getDeltas() const;
};

