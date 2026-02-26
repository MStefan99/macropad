#include "macropad.hpp"
#include "pluginDefinitions/firefoxDefinition.hpp"
#include "pluginDefinitions/kritaDefinition.hpp"
#include "pluginDefinitions/systemQuickDefinition.hpp"


static QuickPlugin systemPlugin {pluginEnvironment, systemQuickDefinition};
static QuickPlugin firefoxPlugin {pluginEnvironment, firefoxDefinition};
static ComboPlugin kritaPlugin {pluginEnvironment, kritaDefinition};

Plugin* plugins[] {&systemPlugin, &firefoxPlugin, &kritaPlugin};

uint8_t pluginCount {sizeof(plugins) / sizeof(plugins[0])};
