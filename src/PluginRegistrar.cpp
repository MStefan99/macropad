#include "macropad.hpp"
#include "pluginDefinitions/systemQuickDefinition.hpp"


static QuickPlugin systemPlugin {pluginEnvironment, systemQuickDefinition};

Plugin* plugins[16] {&systemPlugin};  // System plugin has to come first
uint8_t pluginCount {1};
uint8_t pluginCapacity {sizeof(plugins) / sizeof(plugins[0])};

PluginRegistrar::PluginRegistrar(Plugin& plugin) {
	if (pluginCount < pluginCapacity) {
		plugins[pluginCount++] = &plugin;
	}
}
