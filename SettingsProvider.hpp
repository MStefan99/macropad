#ifndef SETTINGS_PROVIDER_HPP
#define SETTINGS_PROVIDER_HPP

#include "Arduino.h"
#include "EEPROM.h"

namespace settingsProvider {
	struct __attribute__((packed)) Settings {
		int8_t  brightness {31};
		bool    soundEnabled {false};
		uint8_t encoderDivisor {4};
	};

	Settings& getSettings();
	void      setSettings(const Settings& settings);
	void      commitSettings();
};

#endif
