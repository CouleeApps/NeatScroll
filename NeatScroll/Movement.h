#pragma once

#include <vector>
#include "Touchpad.hpp"

struct Movement {
public:
	int mPointCount;
	std::vector<Touchpad::TouchPoint> mPoints;
	std::vector<Touchpad::TouchPoint> mStartPoints;

	std::vector<glm::lvec3> getDeltas() const { return getDeltas(mStartPoints, mPoints); }
	std::vector<glm::vec3> getRelativeDeltas() const { return getRelativeDeltas(mStartPoints, mPoints); }
	glm::vec3 getAverageDelta() const { return getAverageDelta(mStartPoints, mPoints); }
	glm::vec3 getAverageRelativeDelta() const { return getAverageRelativeDelta(mStartPoints, mPoints); }

	static std::vector<glm::lvec3> getDeltas(
			const std::vector<Touchpad::TouchPoint> &start,
			const std::vector<Touchpad::TouchPoint> &end
	);
	static std::vector<glm::vec3> getRelativeDeltas(
			const std::vector<Touchpad::TouchPoint> &start,
			const std::vector<Touchpad::TouchPoint> &end
	);
	static glm::vec3 getAverageDelta(
			const std::vector<Touchpad::TouchPoint> &start,
			const std::vector<Touchpad::TouchPoint> &end
	);
	static glm::vec3 getAverageRelativeDelta(
			const std::vector<Touchpad::TouchPoint> &start,
			const std::vector<Touchpad::TouchPoint> &end
	);
};
