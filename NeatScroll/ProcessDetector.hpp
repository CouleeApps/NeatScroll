//
// Created by glennsmith on 12/17/2017.
//

#ifndef NEATSCROLL_PROCESSDETECTOR_HPP
#define NEATSCROLL_PROCESSDETECTOR_HPP


#include <string>

class ProcessDetector {
	std::string mProcName;
public:
	ProcessDetector(const std::string &procName);

	bool isProcessDetected() const;
};


#endif //NEATSCROLL_PROCESSDETECTOR_HPP
