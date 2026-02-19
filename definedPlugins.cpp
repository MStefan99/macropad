#include "macropad.hpp"
#include "pluginDefinitions/kritaQuickDefinition.hpp"
#include "pluginDefinitions/systemQuickDefinition.hpp"


static auto systemQuickPlugin {
  QuickPlugin {pluginEnvironment, systemQuickDefinition}
};
static auto kritaQuickPlugin {
  QuickPlugin {pluginEnvironment, kritaQuickDefinition}
};


Plugin* definedPlugins[] {/*&systemQuickPlugin,*/ &kritaQuickPlugin};
