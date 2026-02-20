#include "screens.hpp"

#include "screenDefinitions/mainScreenDefinition.hpp"
#include "screenDefinitions/settingsScreenDefinition.hpp"
#include "screenDefinitions/soundScreenDefinition.hpp"


static ListScreen   _mainScreen {pluginEnvironment, mainScreenDefinition};
static ListScreen   _settingsScreen {pluginEnvironment, settingsScreenDefinition};
static OptionScreen _soundScreen {pluginEnvironment, soundScreenDefinition};

Plugin* mainScreen {&_mainScreen};
Plugin* settingsScreen {&_settingsScreen};
Plugin* soundScreen {&_soundScreen};
