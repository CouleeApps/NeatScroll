//
// Created by glennsmith on 12/17/2017.
//

#ifndef NEATSCROLL_PROCESSDETECTOR_H
#define NEATSCROLL_PROCESSDETECTOR_H


#include <string>

class ProcessDetector {
	std::string mProcName;
public:
	ProcessDetector(const std::string &procName);

	bool isProcessDetected() const;
};


#endif //NEATSCROLL_PROCESSDETECTOR_H
