#pragma once
#include <vector>
#include <functional>

class TouchpadUpdateHandler;
class Touchpad {
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

		glm::lvec3 origin;
		glm::lvec3 delta;
		glm::lvec3 scale;
		long palm;

		Buttons buttons;
	};

	Touchpad() {}
	virtual ~Touchpad() {}
	
	/**
	 * Set the handler to receive updates of touchpad input
	 */
	void setHandler(TouchpadUpdateHandler *handler) { mHandler = handler; }

	/**
	 * Connect to the touchpad device
	 * @return If it was successful
	 */
	virtual bool connect() = 0;

	/**
	 * Acquire control over the touchpad
	 * @param exclusive If the control should disable default functionality
	 * @return If it was successful
	 */
	virtual bool acquire(bool exclusive) const = 0;

	/**
	 * Disconnect from the device and free resources
	 * @return If it was successful
	 */
	virtual bool disconnect() = 0;

	/**
	* Poll device, any updates in touches will be fired off to the callback function
	* @return If it was successful
	*/
	virtual bool poll() = 0;

	virtual bool postMouseMove(int dx, int dy, Buttons buttons) = 0;
	virtual bool postMouseScroll(int dx, int dy, Buttons buttons) = 0;
	virtual bool postMouseDown(Buttons buttons) = 0;
	virtual bool postMouseUp(Buttons buttons) = 0;

protected:
	TouchpadUpdateHandler *mHandler;
};

class TouchpadUpdateHandler {
public:
	virtual void update(const std::vector<Touchpad::TouchPoint> &points) = 0;
};
