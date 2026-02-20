#ifndef PLUGIN_HPP
#define PLUGIN_HPP


#include "Arduino.h"

#include "PluginEnvironment.hpp"


#ifndef ALLOW_STORAGE
	#pragma GCC poison EEPROM SettingsProvider
#endif

#ifndef ALLOW_HARDWARE
	#undef digitalPinToInterrupt
	#pragma GCC poison Adafruit_SH1106G Adafruit_NeoPixel Keyboard Tone pinMode digitalWrite digitalRead analogWrite analogRead digitalPinToInterrupt attachInterrupt delay delayMicroseconds
#endif


class Plugin {
public:
	Plugin() = default;
	virtual ~Plugin() = default;

	virtual void onActivate();
	virtual void onDeactivate();

	virtual void onKeyDown(uint8_t key) = 0;
	virtual void onKeyUp(uint8_t key);
	virtual void onEncoderDown(int32_t count);
	virtual void onEncoderUp(int32_t count);

	virtual const char* getName() const;
	virtual const char* getDisplayName() const;

	// Should return true if plugin did some work during the tick for optimal scheduling
	virtual void onTick();
};


#endif
