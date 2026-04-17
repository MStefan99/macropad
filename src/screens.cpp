#include "screens.hpp"

#include "PluginRegistrar.hpp"
#include "screenDefinitions/brightnessScreenDefinition.hpp"
#include "screenDefinitions/mainScreenDefinition.hpp"
#include "screenDefinitions/settingsScreenDefinition.hpp"
#include "screenDefinitions/speedScreenDefinition.hpp"
#include "screenDefinitions/timeoutScreenDefinition.hpp"

ListScreen::Definition appsScreenDefinition {
  "s_apps",
  "Apps",
  "Apps",
  {{"Back",
    [](uint8_t i) {
	navigator.close();
},
    icons::exit}},
  1
};

void activatePlugin(uint8_t idx) {
	navigator.close();  // Close apps screen
	navigator.close();  // Close main menu screen
	navigator.close();  // Close currently open plugin
	navigator.open(plugins[idx - 1]);
}

void populateAppsScreen() {
	uint8_t screenDefinitionCount =
	    sizeof(ListScreen::Definition::items) / sizeof(ListScreen::Definition::items[0]) - 1;  // -1 for the back button

	for (uint8_t i {1}; i <= min(pluginCount, screenDefinitionCount); ++i) {
		auto* plugin {plugins[i - 1]};
		auto* name {plugin->getShortDisplayName()};

		for (uint8_t j {0}; j < 8 && name[j]; ++j) {
			appsScreenDefinition.items[i].displayName[j] = name[j];
		}
		appsScreenDefinition.items[i].displayName[7] = 0;
		appsScreenDefinition.items[i].callback = activatePlugin;

		if (plugin->getIcon()) {
			appsScreenDefinition.items[i].icon = plugin->getIcon();
		} else {
			appsScreenDefinition.items[i].icon = icons::app;
		}
	}
}

static ListScreen   _mainScreen {pluginEnvironment, mainScreenDefinition};
static ListScreen   _appsScreen {pluginEnvironment, appsScreenDefinition};
static ListScreen   _settingsScreen {pluginEnvironment, settingsScreenDefinition};
static ValueScreen  _brightnessScreen {pluginEnvironment, brightnessScreenDefinition};
static SelectScreen _speedScreen {pluginEnvironment, speedScreenDefinition};
static SelectScreen _timeoutScreen {pluginEnvironment, timeoutScreenDefinition};

Plugin* mainScreen {&_mainScreen};
Plugin* appsScreen(&_appsScreen);
Plugin* settingsScreen {&_settingsScreen};
Plugin* brightnessScreen {&_brightnessScreen};
Plugin* speedScreen {&_speedScreen};
Plugin* timeoutScreen {&_timeoutScreen};
