#pragma once
#include "Touchpad.hpp"
#include <SynKit.h>

class SynapticsTouchpad : public Touchpad {
public:
	SynapticsTouchpad();
	~SynapticsTouchpad() override;

	/**
	* Connect to the touchpad device
	* @return If it was successful
	*/
	bool connect() override;

	/**
	* Acquire control over the touchpad
	* @param exclusive If the control should disable default functionality
	* @return If it was successful
	*/
	bool acquire(bool exclusive) const override;

	/**
	* Disconnect from the device and free resources
	* @return If it was successful
	*/
	bool disconnect() override;

	/**
	* Poll device, any updates in touches will be fired off to the callback function
	* @return If it was successful
	*/
	bool poll() override;

	bool postMouseMove(int dx, int dy, Buttons buttons) override;
	bool postMouseScroll(int dx, int dy, Buttons buttons) override;
	bool postMouseDown(Buttons buttons) override;
	bool postMouseUp(Buttons buttons) override;

private:
	HANDLE mEvent;
	long mMaxFingers;

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

