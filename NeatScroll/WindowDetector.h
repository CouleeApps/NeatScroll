//
// Created by glennsmith on 12/24/2017.
//

#ifndef NEATSCROLL_WINDOWDETECTOR_H
#define NEATSCROLL_WINDOWDETECTOR_H


#include <string>

class WindowDetector {
	std::string mWindowName;
public:
	WindowDetector(const std::string &windowName);

	bool isWindowDetected() const;
};

#endif //NEATSCROLL_WINDOWDETECTOR_H
