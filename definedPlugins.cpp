#include "macropad.hpp"
#include "pluginDefinitions/TestPluginDefinition.hpp"


static auto testPlugin {
  QuickPlugin {pluginEnvironment, testPluginDefinition}
};

Plugin* definedPlugins[] {&testPlugin};
