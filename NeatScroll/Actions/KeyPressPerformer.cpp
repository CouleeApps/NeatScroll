//
// Created by glennsmith on 12/17/2017.
//

#include "stdafx.h"
#include "KeyPressPerformer.hpp"
#include <Windows.h>

KeyPressPerformer::KeyPressPerformer(const std::vector<int> &mKeycodes) : mKeycodes(mKeycodes) {}

bool KeyPressPerformer::onGestureStart(const Movement &movement) {
	//Press
	std::vector<INPUT> inputs(mKeycodes.size());
	for (auto i = 0; i < mKeycodes.size(); i ++) {
		inputs[i] = { 0 };
		inputs[i].type = INPUT_KEYBOARD;
		inputs[i].ki.wVk = static_cast<WORD>(mKeycodes[i]);
	}
	SendInput(static_cast<UINT>(mKeycodes.size()), inputs.data(), sizeof(INPUT));

	//Unpress
	for (auto i = 0; i < mKeycodes.size(); i ++) {
		inputs[i].ki.dwFlags = KEYEVENTF_KEYUP;
	}
	SendInput(static_cast<UINT>(mKeycodes.size()), inputs.data(), sizeof(INPUT));

	return true;
}

bool KeyPressPerformer::onGestureMove(const Movement &movement) {
	return true;
}

bool KeyPressPerformer::onGestureStop(const Movement &movement) {
	return true;
}
