#include "SettingsProvider.hpp"


constexpr static uint32_t storageSize {256};

static settingsProvider::Settings _settings {};
static bool                       _loaded {false};
static bool                       _dirty {false};

settingsProvider::Settings _sanitize(const settingsProvider::Settings& settings) {
	return settings;
}

settingsProvider::Settings& settingsProvider::getSettings() {
	if (!_loaded) {
		_loaded = true;
		EEPROM.begin(storageSize);
		EEPROM.get(0, _settings);
	}

	return _settings;
}

void settingsProvider::setSettings(const settingsProvider::Settings& settings) {
	settingsProvider::getSettings();

	_settings = _sanitize(settings);
	EEPROM.put(0, _settings);
	_dirty = true;
}

void settingsProvider::commitSettings() {
	if (_dirty) {
		_dirty = false;
		EEPROM.commit();
	}
}
