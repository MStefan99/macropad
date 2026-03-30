#include "KeyDispatcher.hpp"

KeyDispatcher::KeyDispatcher(DispatchCallbackType dispatchCallback, TypeCallbackType typeCallback):
  _dispatchCallback {dispatchCallback},
  _typeCallback {typeCallback} {
	// Nothing to do
}

void KeyDispatcher::dispatch(const uint8_t keys[6], uint16_t consumerKey, uint32_t duration) {
	if (_dispatchCallback) {
		_dispatchCallback(keys, consumerKey, duration);
	}
}

void KeyDispatcher::type(const char* string, uint8_t len, uint32_t delay) {
	if (_typeCallback) {
		_typeCallback(string, len, delay);
	}
}
