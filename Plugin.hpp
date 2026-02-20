#ifndef PLUGIN_HPP
#define PLUGIN_HPP


#include "Adafruit_SH110X.h"
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
	Plugin(PluginEnvironment& environment);
	virtual ~Plugin() = default;

	virtual void onActivate();
	virtual void onResume() = 0;
	virtual void onSuspend();
	virtual void onDeactivate();

	virtual void onKeyDown(uint8_t key);
	virtual void onKeyUp(uint8_t key) = 0;
	virtual void onEncoderDown(int32_t count);
	virtual void onEncoderUp(int32_t count);

	virtual const char*    getName() const;
	virtual const char*    getDisplayName() const;
	virtual const uint8_t* getIcon() const;

	virtual void onTick();

protected:
	PluginEnvironment& _environment;
};


#endif
