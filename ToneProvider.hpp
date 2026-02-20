#ifndef PLUGIN_TONE_HPP
#define PLUGIN_TONE_HPP


#include "Arduino.h"

class ToneProvider {
public:
	using CallbackType = void (*)(unsigned int frequency, unsigned long duration);

	ToneProvider(CallbackType toneCallback = nullptr);

	void tone(unsigned int frequency, unsigned long duration);

protected:
	CallbackType _toneCallback {};
};


#endif
