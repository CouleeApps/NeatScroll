#include <SynKit.h>
#include <vector>

class TouchpadManager {
public:
	struct TouchPoint {
		int index;
		long timestamp;

		glm::vec2 origin;
		glm::vec2 delta;
		glm::vec2 scale;
		float size;
		long palm;
	};

	typedef void(*CallbackFn)(const std::vector<TouchPoint> &points);
	
	TouchpadManager(CallbackFn callback);
	
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
};