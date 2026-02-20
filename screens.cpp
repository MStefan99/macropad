#include "screens.hpp"

#include "plugins.hpp"
#include "screenDefinitions/brightnessScreenDefinition.hpp"
#include "screenDefinitions/mainScreenDefinition.hpp"
#include "screenDefinitions/settingsScreenDefinition.hpp"
#include "screenDefinitions/soundScreenDefinition.hpp"
#include "screenDefinitions/speedScreenDefinition.hpp"
#include "screenDefinitions/timeoutScreenDefinition.hpp"

ListScreen::Definition appsScreenDefinition {"s_apps", "Apps", {}, 0};

void activatePlugin(uint8_t idx) {
	navigator.close();  // Close apps screen
	navigator.close();  // Close main menu screen
	navigator.open(plugins[idx]);
}

void populateAppsScreen() {
	uint8_t screenDefinitionCount = sizeof(ListScreen::Definition::items) / sizeof(ListScreen::Definition::items[0]);

	for (uint8_t i {0}; i < min(pluginCount, screenDefinitionCount); ++i) {
		auto* name {plugins[i]->getDisplayName()};
		for (uint8_t j {0}; j < 16 && name[j]; ++j) {
			appsScreenDefinition.items[i].displayName[j] = name[j];
		}
		appsScreenDefinition.items[i].callback = activatePlugin;
		appsScreenDefinition.items[i].icon = plugins[i]->getIcon();
	}
}

static ListScreen   _mainScreen {pluginEnvironment, mainScreenDefinition};
static ListScreen   _appsScreen {pluginEnvironment, appsScreenDefinition};
static ListScreen   _settingsScreen {pluginEnvironment, settingsScreenDefinition};
static ValueScreen  _brightnessScreen {pluginEnvironment, brightnessScreenDefinition};
static SelectScreen _speedScreen {pluginEnvironment, speedScreenDefinition};
static OptionScreen _soundScreen {pluginEnvironment, soundScreenDefinition};
static SelectScreen _timeoutScreen {pluginEnvironment, timeoutScreenDefinition};

Plugin* mainScreen {&_mainScreen};
Plugin* appsScreen(&_appsScreen);
Plugin* settingsScreen {&_settingsScreen};
Plugin* brightnessScreen {&_brightnessScreen};
Plugin* speedScreen {&_speedScreen};
Plugin* soundScreen {&_soundScreen};
Plugin* timeoutScreen {&_timeoutScreen};
