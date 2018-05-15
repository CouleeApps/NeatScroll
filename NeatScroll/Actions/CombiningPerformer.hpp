//
// Created by glennsmith on 12/17/2017.
//

#ifndef NEATSCROLL_COMBININGPERFORMER_HPP
#define NEATSCROLL_COMBININGPERFORMER_HPP

#include "../Gesture.hpp"

class CombiningPerformer : Gesture::Performer {
	std::vector<Gesture::Performer *> mPerformers;
public:
	template<typename ...Args>
	CombiningPerformer(Args ...args) {
		mPerformers.push_back(args...);
	}

	bool onGestureStart(const Movement &movement) override;
	bool onGestureMove(const Movement &movement) override;
	bool onGestureStop(const Movement &movement) override;
};


#endif //NEATSCROLL_COMBININGPERFORMER_HPP
