#pragma once
#include <SynKit.h>
#include <vector>
#include <functional>

class TouchpadManager {
public:
	struct Buttons {
		int Left : 1;
		int Middle : 1;
		int Right : 1;
		int Button4 : 1;
		int Button5 : 1;

		Buttons() {
			Left = Middle = Right = Button4 = Button5 = 0;
		}
		void copy(const Buttons &other) {
			Left = other.Left;
			Middle = other.Middle;
			Right = other.Right;
			Button4 = other.Button4;
			Button5 = other.Button5;
		}
		Buttons(const Buttons &other) {
			copy(other);
		}
		Buttons& operator=(const Buttons &other) {
			copy(other);
			return *this;
		}
	};

	struct TouchPoint {
		int index;
		long timestamp;

		glm::lvec2 origin;
		glm::lvec2 delta;
		glm::lvec2 scale;
		long size;
		long palm;

		Buttons buttons;
	};

	typedef std::function<void(const std::vector<TouchPoint> &points)> CallbackFn;
	
	TouchpadManager();
	
	/**
	 * Set the callback function to receive updates of touchpad input
	 */
	void setCallback(CallbackFn callback) { mCallback = callback; }

	/**
	 * Connect to the touchpad device
	 * @return If it was successful
	 */
	bool connect();

	/**
	 * Acquire control over the touchpad
	 * @param exclusive If the control should disable default functionality
	 * @return If it was successful
	 */
	bool acquire(bool exclusive) const;

	/**
	 * Disconnect from the device and free resources
	 * @return If it was successful
	 */
	bool disconnect();

	/**
	* Poll device, any updates in touches will be fired off to the callback function
	* @return If it was successful
	*/
	bool poll();

	bool postMouseMove(int dx, int dy, Buttons buttons);
	bool postMouseScroll(int dx, int dy, Buttons buttons);
	bool postMouseDown(Buttons buttons);
	bool postMouseUp(Buttons buttons);

private:
	HANDLE mEvent;
	long mMaxFingers;
	CallbackFn mCallback;

	ISynAPI    *mAPI;
	ISynDevice *mDevice;
	ISynGroup  *mGroup;
	ISynPacket *mPacket;

	struct Bounds {
		glm::lvec3 min;
		glm::lvec3 max;
	} mBounds;

	static Buttons buttonStateToButtons(long buttonState);
	static long buttonsToButtonState(Buttons buttons);
};