//
// Created by glennsmith on 12/17/2017.
//

#ifndef NEATSCROLL_KEYPRESSPERFORMER_H
#define NEATSCROLL_KEYPRESSPERFORMER_H


#include "../Gesture.hpp"

class KeyPressPerformer : public Gesture::Performer {
	std::vector<int> mKeycodes;

public:
	KeyPressPerformer(const std::vector<int> &mKeycodes);

	bool onGestureStart(const Movement &movement) override;
	bool onGestureMove(const Movement &movement) override;
	bool onGestureStop(const Movement &movement) override;

};


#endif //NEATSCROLL_KEYPRESSPERFORMER_H
