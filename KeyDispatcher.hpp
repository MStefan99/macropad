#ifndef KEY_DISPATCHER_HPP
#define KEY_DISPATCHER_HPP


#include "Arduino.h"


class KeyDispatcher {
public:
	using CallbackType = void (*)(const uint8_t keys[6], uint16_t consumerKey, uint32_t duration);

	KeyDispatcher(CallbackType dispatchCallback = nullptr);

	void dispatch(const uint8_t keys[6], uint16_t consumerKey = 0, uint32_t duration = 10);

protected:
	CallbackType _dispatchCallback {};
};


#endif
