#include "screens.hpp"

#include "screenDefinitions/brightnessScreenDefinition.hpp"
#include "screenDefinitions/mainScreenDefinition.hpp"
#include "screenDefinitions/settingsScreenDefinition.hpp"
#include "screenDefinitions/soundScreenDefinition.hpp"
#include "screenDefinitions/speedScreenDefinition.hpp"
#include "screenDefinitions/timeoutScreenDefinition.hpp"


static ListScreen   _mainScreen {pluginEnvironment, mainScreenDefinition};
static ListScreen   _settingsScreen {pluginEnvironment, settingsScreenDefinition};
static ValueScreen  _brightnessScreen {pluginEnvironment, brightnessScreenDefinition};
static SelectScreen _speedScreen {pluginEnvironment, speedScreenDefinition};
static OptionScreen _soundScreen {pluginEnvironment, soundScreenDefinition};
static SelectScreen _timeoutScreen {pluginEnvironment, timeoutScreenDefinition};

Plugin* mainScreen {&_mainScreen};
Plugin* settingsScreen {&_settingsScreen};
Plugin* brightnessScreen {&_brightnessScreen};
Plugin* speedScreen {&_speedScreen};
Plugin* soundScreen {&_soundScreen};
Plugin* timeoutScreen {&_timeoutScreen};
