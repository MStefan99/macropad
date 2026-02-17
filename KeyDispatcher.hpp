#ifndef KEY_DISPATCHER_HPP
#define KEY_DISPATCHER_HPP

#include "Arduino.h"

class KeyDispatcher {
public:
	using CallbackType = void (*)(uint8_t keys[6], uint32_t timeout);

protected:
	CallbackType _dispatchCallback {};

public:
	KeyDispatcher(CallbackType dispatchCallback = nullptr);

	void dispatch(uint8_t keys[6], uint32_t timeout = 20);
};

#endif
