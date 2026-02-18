#ifndef KEY_DISPATCHER_HPP
#define KEY_DISPATCHER_HPP


#include "Arduino.h"


class KeyDispatcher {
public:
	using CallbackType = void (*)(const uint16_t keys[6], bool consumerKeys, uint32_t duration);

	KeyDispatcher(CallbackType dispatchCallback = nullptr);

	void dispatch(const uint16_t keys[6], bool consumerKeys = false, uint32_t duration = 10);

protected:
	CallbackType _dispatchCallback {};
};


#endif
