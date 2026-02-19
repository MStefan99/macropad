#include "macropad.hpp"
#include "pluginDefinitions/kritaComboDefinition.hpp"
#include "pluginDefinitions/systemQuickDefinition.hpp"


static auto systemPlugin {
  QuickPlugin {pluginEnvironment, systemQuickDefinition}
};
static auto kritaPlugin {
  ComboPlugin {pluginEnvironment, kritaComboDefinition}
};


Plugin* definedPlugins[] {/*&systemPlugin,*/ &kritaPlugin};
