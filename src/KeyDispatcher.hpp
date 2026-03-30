#ifndef KEY_DISPATCHER_HPP
#define KEY_DISPATCHER_HPP


#include "Arduino.h"

class KeyDispatcher {
public:
	using DispatchCallbackType = void (*)(const uint8_t keys[8], uint16_t consumerKey, uint32_t duration);
	using TypeCallbackType = void     (*)(const char* string, uint8_t len, uint32_t delay);

	KeyDispatcher(DispatchCallbackType dispatchCallback = nullptr, TypeCallbackType typecallback = nullptr);

	void dispatch(const uint8_t keys[8], uint16_t consumerKey = 0, uint32_t duration = 10);
	void type(const char* string, uint8_t len, uint32_t duration = 10);

protected:
	DispatchCallbackType _dispatchCallback {};
	TypeCallbackType     _typeCallback {};
};


#endif
