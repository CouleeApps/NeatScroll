#pragma once
#include "Touchpad.hpp"
#include <SynKit.h>

class SynapticsTouchpad : public Touchpad {
public:
	SynapticsTouchpad();
	virtual ~SynapticsTouchpad();

	/**
	* Connect to the touchpad device
	* @return If it was successful
	*/
	virtual bool connect() override;

	/**
	* Acquire control over the touchpad
	* @param exclusive If the control should disable default functionality
	* @return If it was successful
	*/
	virtual bool acquire(bool exclusive) const override;

	/**
	* Disconnect from the device and free resources
	* @return If it was successful
	*/
	virtual bool disconnect() override;

	/**
	* Poll device, any updates in touches will be fired off to the callback function
	* @return If it was successful
	*/
	virtual bool poll() override;

	virtual bool postMouseMove(int dx, int dy, Buttons buttons) override;
	virtual bool postMouseScroll(int dx, int dy, Buttons buttons) override;
	virtual bool postMouseDown(Buttons buttons) override;
	virtual bool postMouseUp(Buttons buttons) override;

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

