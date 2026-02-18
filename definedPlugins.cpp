#include "macropad.hpp"
#include "pluginDefinitions/kritaQuickDefinition.hpp"


static auto kritaQuickPlugin {
  QuickPlugin {pluginEnvironment, kritaQuickDefinition}
};


Plugin* definedPlugins[] {&kritaQuickPlugin};
