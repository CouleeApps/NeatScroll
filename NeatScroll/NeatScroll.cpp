#include "stdafx.h"
#include <functional>
#include "Touchpad.hpp"
#include "SynapticsTouchpad.hpp"
#include "MovementDetector.hpp"
#include "GestureHandler.hpp"
#include "Actions/ConditionalPerformer.h"
#include "Actions/KeyPressPerformer.h"
#include "Gestures/SwipeGestureRecognizer.h"
#include "ProcessDetector.h"
#include "WindowDetector.h"
#include "HighPerformanceTimer.h"
#include <thread>

int main(int argc, const char **argv) {
	using namespace std::placeholders;

	SynapticsTouchpad touchpad;
	MovementDetector detector(touchpad);
	GestureHandler handler;
	touchpad.setHandler(&detector);
	detector.setGestureHandler(&handler);

	//Raii timers
	auto up3Timer = std::make_shared<HighPerformanceTimer>();
	auto down3Timer = std::make_shared<HighPerformanceTimer>();
	auto left3Timer = std::make_shared<HighPerformanceTimer>();
	auto right3Timer = std::make_shared<HighPerformanceTimer>();

	//Gesture recognizers
	auto up3Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Up, 3, 0.1f, 1.f, up3Timer.get());
	auto down3Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Down, 3, 0.1f, 1.f, down3Timer.get());
	auto left3Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Left, 3, 0.1f, 1.f, left3Timer.get());
	auto right3Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Right, 3, 0.1f, 1.f, right3Timer.get());

	//Detect task view by its active window in the foreground
	auto taskViewProcessDetector = ProcessDetector("explorer.exe");
	auto taskViewWindowDetector = WindowDetector("Task View");
	auto isTaskView = [&]() {
		return taskViewProcessDetector.isProcessDetected() && taskViewWindowDetector.isWindowDetected();
	};

	//Gesture performers
	auto winTabPerf = KeyPressPerformer({ VK_LWIN, VK_TAB });
	auto openTaskViewPerf = ConditionalPerformer{ winTabPerf, [&isTaskView]() { return !isTaskView(); } };
	auto closeTaskViewPerf = ConditionalPerformer{ winTabPerf, isTaskView };
	auto vDeskLeftPerf = KeyPressPerformer({ VK_LWIN, VK_LCONTROL, VK_LEFT });
	auto vDeskRightPerf = KeyPressPerformer({ VK_LWIN, VK_LCONTROL, VK_RIGHT });

	//Construct and add the actual gestures
	Gesture ffuGesture{ up3Rec, openTaskViewPerf };
	Gesture ffdGesture{ down3Rec, closeTaskViewPerf };
	Gesture fflGesture{ left3Rec, vDeskLeftPerf };
	Gesture ffrGesture{ right3Rec, vDeskRightPerf };
	handler.addGesture(&ffuGesture);
	handler.addGesture(&ffdGesture);
	handler.addGesture(&fflGesture);
	handler.addGesture(&ffrGesture);

	auto chromeDetector = ProcessDetector("chrome.exe");

	auto left2Timer = std::make_shared<HighPerformanceTimer>();
	auto right2Timer = std::make_shared<HighPerformanceTimer>();

	auto left2Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Left, 2, 0.2f, 0.1f, left2Timer.get());
	auto backPerf = KeyPressPerformer({ VK_BROWSER_BACK });
	auto chromeBackPerf = ConditionalPerformer(backPerf, [&chromeDetector]() { return chromeDetector.isProcessDetected(); });
	auto backGest = Gesture(left2Rec, chromeBackPerf);
	handler.addGesture(&backGest);

	auto right2Rec = SwipeGestureRecognizer(SwipeGestureRecognizer::Right, 2, 0.2f, 0.1f, right2Timer.get());
	auto forwardPerf = KeyPressPerformer({ VK_BROWSER_FORWARD });
	auto chromeForwardPerf = ConditionalPerformer(forwardPerf, [&chromeDetector]() { return chromeDetector.isProcessDetected(); });
	auto forwardGest = Gesture(right2Rec, chromeForwardPerf);
	handler.addGesture(&forwardGest);

	if (!touchpad.connect()) {
		fprintf(stderr, "Could not connect to touchpad\n");
		return EXIT_FAILURE;
	}

	//To disable the system using this, uncomment this line.
	// Just make sure you have a mouse nearby in case the program crashes
	touchpad.acquire(true);

	while (true) {
		if (!touchpad.poll()) {
			break;
		}
		//Performance
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	if (!touchpad.disconnect()) {
		fprintf(stderr, "Error disconnecting touchpad\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
