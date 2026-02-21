#include "macropad.hpp"
#include "pluginDefinitions/kritaComboDefinition.hpp"
#include "pluginDefinitions/systemQuickDefinition.hpp"


static QuickPlugin systemPlugin {pluginEnvironment, systemQuickDefinition};
static ComboPlugin kritaPlugin {pluginEnvironment, kritaComboDefinition};

Plugin* plugins[] {&systemPlugin, &kritaPlugin};
uint8_t pluginCount {sizeof(plugins) / sizeof(plugins[0])};
