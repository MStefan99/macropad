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
	#pragma GCC poison Serial Adafruit_SH1106G Adafruit_NeoPixel Keyboard tone pinMode digitalWrite digitalRead analogWrite analogRead digitalPinToInterrupt attachInterrupt delay delayMicroseconds
#endif


class Plugin {
public:
	Plugin(PluginEnvironment& environment);
	virtual ~Plugin() = default;

	// Called when the plugin is initialized.
	// Plugins are not guaranteed to be destroyed between activations,
	// so make sure to initialize your internal state here
	virtual void onActivate();
	// Called when the plugin is about to being shown on screen
	// Draw the UI and set up backlight here
	virtual void onResume() = 0;
	// Called when the plugin is about to move to background
	virtual void onSuspend();
	// Called when the plugin is about to be deactivated
	virtual void onDeactivate();

	virtual void onKeyDown(uint8_t key);
	virtual void onKeyUp(uint8_t key);
	virtual void onEncoderDown(int32_t count);
	virtual void onEncoderUp(int32_t count);

	// Called when data is received from the computer
	virtual void onData(char* string);

	virtual const char*     getName() const;
	virtual const char*     getDisplayName() const;
	virtual const char*     getShortDisplayName() const;
	virtual const uint32_t* getIcon() const;

	// Called every millisecond when the plugin is in the foreground (resumed)
	virtual void onTick();

protected:
	PluginEnvironment& _environment;
};


#endif
