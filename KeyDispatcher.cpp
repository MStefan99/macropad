#include "KeyDispatcher.hpp"

KeyDispatcher::KeyDispatcher(CallbackType dispatchCallback):
  _dispatchCallback {dispatchCallback} {
	// Nothing to do
}

void KeyDispatcher::dispatch(const uint16_t keys[6], bool consumerKeys, uint32_t duration) {
	if (_dispatchCallback) {
		_dispatchCallback(keys, consumerKeys, duration);
	}
}
