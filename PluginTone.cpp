#include "PluginTone.hpp"

PluginTone::PluginTone(CallbackType toneCallback):
  _toneCallback {toneCallback} {
	// Nothing to do
}

void PluginTone::tone(unsigned int frequency, unsigned long duration) {
	if (_toneCallback) {
		_toneCallback(frequency, duration);
	}
}
