#include "KeyDispatcher.hpp"

KeyDispatcher::KeyDispatcher(CallbackType dispatchCallback):
  _dispatchCallback {dispatchCallback} {
	// Nothing to do
}

void KeyDispatcher::dispatch(const uint8_t keys[6], uint16_t consumerKey, uint32_t duration) {
	if (_dispatchCallback) {
		_dispatchCallback(keys, consumerKey, duration);
	}
}
