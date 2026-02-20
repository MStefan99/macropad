#include "screens.hpp"

#include "screenDefinitions/mainScreenDefinition.hpp"


static ListScreen _mainScreen {pluginEnvironment, mainScreenDefinition};
Plugin*           mainScreen {&_mainScreen};
