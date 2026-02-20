#include "screens.hpp"

#include "screenDefinitions/mainScreenDefinition.hpp"
#include "screenDefinitions/settingsScreenDefinition.hpp"


static ListScreen _mainScreen {pluginEnvironment, mainScreenDefinition};
static ListScreen _settingsScreen {pluginEnvironment, settingsScreenDefinition};

Plugin* mainScreen {&_mainScreen};
Plugin* settingsScreen {&_settingsScreen};
