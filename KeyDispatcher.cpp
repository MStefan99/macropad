#include "KeyDispatcher.hpp"

KeyDispatcher::KeyDispatcher(CallbackType dispatchCallback):
  _dispatchCallback {dispatchCallback} {
	// Nothing to do
}

void KeyDispatcher::dispatch(uint8_t keys[6], uint32_t timeout) {
	if (_dispatchCallback) {
		_dispatchCallback(keys, timeout);
	}
}
