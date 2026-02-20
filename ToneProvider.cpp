#include "ToneProvider.hpp"

ToneProvider::ToneProvider(CallbackType toneCallback):
  _toneCallback {toneCallback} {
	// Nothing to do
}

void ToneProvider::tone(unsigned int frequency, unsigned long duration) {
	if (_toneCallback) {
		_toneCallback(frequency, duration);
	}
}
