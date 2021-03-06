#include "stdafx.h"
#include "SynapticsTouchpad.hpp"

//Convenience
#define OR_FALSE(test) if (!(test)) { return false; }
#define OK_OR_FALSE(test) if ((test) != SYN_OK) { return false; }
#define OK_OR_CONT(test) if ((test) != SYN_OK) { continue; }

SynapticsTouchpad::SynapticsTouchpad() : Touchpad() {

}

SynapticsTouchpad::~SynapticsTouchpad() {

}

bool SynapticsTouchpad::connect() {
	//Init touchpad api
	OK_OR_FALSE(SynCreateAPI(&mAPI));

	//Find and create the touchpad device connection
	LONG handle = -1;
	OK_OR_FALSE(mAPI->FindDevice(SE_ConnectionAny, SE_DeviceTouchPad, &handle));
	OK_OR_FALSE(mAPI->CreateDevice(handle, &mDevice));

	//Create an event to use for polling updates to the touchpad
	OR_FALSE((mEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) != NULL);
	OK_OR_FALSE(mDevice->SetEventNotification(mEvent));
	OK_OR_FALSE(mAPI->SetEventNotification(mEvent));

	//Enable multi finger support
	OK_OR_FALSE(mDevice->SetProperty(SP_IsMultiFingerReportEnabled, 1));
	OK_OR_FALSE(mDevice->SetProperty(SP_IsGroupReportEnabled, 1));

	//Max finger count
	OK_OR_FALSE(mDevice->GetProperty(SP_NumMaxReportedFingers, &mMaxFingers));

	//Create structures for receiving data from the touchpad
	OK_OR_FALSE(mDevice->CreateGroup(&mGroup));
	OK_OR_FALSE(mDevice->CreatePacket(&mPacket));

	//Bounds of the sensors, values in comments are what my device reads

	//1024 -> 5888
	OK_OR_FALSE(mDevice->GetProperty(SP_XLoSensor, &mBounds.min.x));
	OK_OR_FALSE(mDevice->GetProperty(SP_XHiSensor, &mBounds.max.x));
	//1024 -> 4864
	OK_OR_FALSE(mDevice->GetProperty(SP_YLoSensor, &mBounds.min.y));
	OK_OR_FALSE(mDevice->GetProperty(SP_YHiSensor, &mBounds.max.y));
	//0 -> 255
	mBounds.min.z = 0; //No property for this one
	OK_OR_FALSE(mDevice->GetProperty(SP_ZMaximum, &mBounds.max.z));

	return true;
}


bool SynapticsTouchpad::acquire(bool exclusive) const {
	OK_OR_FALSE(mDevice->Acquire(exclusive ? SE_AcquireExclusive : SE_AcquirePassive));
	return true;
}

bool SynapticsTouchpad::disconnect() {
	//Stop sending events
	OK_OR_FALSE(mDevice->SetEventNotification(NULL));

	//Cleanup anything we've created
	OK_OR_FALSE(mDevice->Release());
	OK_OR_FALSE(mAPI->Release());
	OR_FALSE(CloseHandle(mEvent) != 0);

	return true;
}

bool SynapticsTouchpad::poll() {
	//Check for new events
	OR_FALSE(WaitForSingleObject(mEvent, 0) != WAIT_FAILED);

	acquire(false);
	
	//Poll the events until we can't
	while (mDevice->LoadGroup(mGroup) != SYNE_FAIL && mGroup) {
		std::vector<TouchPoint> points;

		//Check each finger for a packet
		for (int i = 0; i < mMaxFingers; ++i) {
			//Get the packet for this finger
			OK_OR_CONT(mGroup->GetPacketByIndex(i, mPacket));

			long timestamp;
			OK_OR_CONT(mPacket->GetProperty(SP_TimeStamp, &timestamp));

			//Is this finger down?
			long fingerState;
			OK_OR_CONT(mPacket->GetProperty(SP_FingerState, &fingerState));
			if (fingerState & SF_FingerPresent) {
				//X/Y position, Z size and W used for palm detection
				long x, y, z, w;
				OK_OR_CONT(mPacket->GetProperty(SP_X, &x));
				OK_OR_CONT(mPacket->GetProperty(SP_Y, &y));
				OK_OR_CONT(mPacket->GetProperty(SP_Z, &z));
				OK_OR_CONT(mPacket->GetProperty(SP_W, &w));

				//Movement
				long dx, dy, dz;
				OK_OR_CONT(mPacket->GetProperty(SP_XDelta, &dx));
				OK_OR_CONT(mPacket->GetProperty(SP_YDelta, &dy));
				OK_OR_CONT(mPacket->GetProperty(SP_ZDelta, &dz));

				long button;
				OK_OR_CONT(mPacket->GetProperty(SP_ButtonState, &button));

				//Structure to feed into the callback 
				TouchPoint tp;
				tp.index = i;
				tp.timestamp = timestamp;
				tp.scale.x = mBounds.max.x - mBounds.min.x;
				tp.scale.y = mBounds.max.y - mBounds.min.y;
				tp.scale.z = mBounds.max.z - mBounds.min.z;
				tp.origin.x = x - mBounds.min.x;
				tp.origin.y = y - mBounds.min.y;
				tp.origin.z = z - mBounds.min.z;
				tp.delta.x = dx;
				tp.delta.y = dy;
				tp.delta.z = dz;
				tp.palm = w;
				tp.buttons = buttonStateToButtons(button);

				points.push_back(tp);
			}
		}
		//Got all the points, let em go
		if (mHandler) {
			mHandler->update(points);
		}
	}

	//Check if the touchpad has disconnected. If it has, we'll get a SE_DevicedAdded and a SE_DeviceRemoved event (same time?)
	// If we get either of those then our current handle is disconnected so we will need to reconnect.
	bool needReconnect = false;
	LONG eventType;
	while (mAPI->GetEventParameter(&eventType) != SYNE_FAIL) {
		switch (eventType) {
		case SE_DeviceAdded:
		case SE_DeviceRemoved:
			//Need to reconnect
			needReconnect = true;
			break;
		default:
			break;
		}
	}
	if (needReconnect) {
		OR_FALSE(disconnect());
		OR_FALSE(connect());
	}

	return true;
}

bool SynapticsTouchpad::postMouseMove(int dx, int dy, Buttons buttons) {
	OK_OR_FALSE(mDevice->ForceMotion(static_cast<LONG>(dx), static_cast<LONG>(dy), buttonsToButtonState(buttons)));

	return true;
}

bool SynapticsTouchpad::postMouseScroll(int dx, int dy, Buttons buttons) {
	if (dx != 0) {
		OK_OR_FALSE(mDevice->ForceMotionWithWheel(0, 0, buttonsToButtonState(buttons), static_cast<LONG>(dx)));
	}
	if (dy != 0) {
		OK_OR_FALSE(mDevice->ForceMotionWithHorizontalWheel(0, 0, buttonsToButtonState(buttons), static_cast<LONG>(dy)));
	}
	return true;
}

bool SynapticsTouchpad::postMouseDown(Buttons buttons) {
	return false;
}

bool SynapticsTouchpad::postMouseUp(Buttons buttons) {
	return false;
}

Touchpad::Buttons SynapticsTouchpad::buttonStateToButtons(long buttonState) {
	Buttons buttons;
	if (buttonState & SF_ButtonLeft)   buttons.Left = 1;
	if (buttonState & SF_ButtonMiddle) buttons.Middle = 1;
	if (buttonState & SF_ButtonRight)  buttons.Right = 1;
	if (buttonState & SF_Button4)      buttons.Button4 = 1;
	if (buttonState & SF_Button5)      buttons.Button5 = 1;
	return buttons;
}
long SynapticsTouchpad::buttonsToButtonState(Touchpad::Buttons buttons) {
	long buttonState = 0;
	if (buttons.Left)    buttonState |= SF_ButtonLeft;
	if (buttons.Middle)  buttonState |= SF_ButtonMiddle;
	if (buttons.Right)   buttonState |= SF_ButtonRight;
	if (buttons.Button4) buttonState |= SF_Button4;
	if (buttons.Button5) buttonState |= SF_Button5;
	return buttonState;
}

bool SynapticsTouchpad::setDeviceProperty(SynDeviceProperty property, long value) {
	OK_OR_FALSE(mDevice->SetProperty(property, value));
	return true;
}

bool SynapticsTouchpad::getDeviceProperty(SynDeviceProperty property, long *value) {
	OK_OR_FALSE(mDevice->GetProperty(property, value));
	return true;
}

bool SynapticsTouchpad::setAPIProperty(SynAPIProperty property, long value) {
	OK_OR_FALSE(mAPI->SetProperty(property, value));
	return true;
}

bool SynapticsTouchpad::getAPIProperty(SynAPIProperty property, long *value) {
	OK_OR_FALSE(mAPI->GetProperty(property, value));
	return true;
}

bool SynapticsTouchpad::persistState() {
	OK_OR_FALSE(mAPI->PersistState(0));
	return true;
}

bool SynapticsTouchpad::restoreState() {
	OK_OR_FALSE(mAPI->RestoreState(0));
	return true;
}
