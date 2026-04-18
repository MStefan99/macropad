#ifndef PLUGIN_REGISTRAR_HPP
#define PLUGIN_REGISTRAR_HPP

#include "Plugin.hpp"
#include "PluginEnvironment.hpp"

extern Plugin* plugins[];
extern uint8_t pluginCount;

extern PluginEnvironment pluginEnvironment;

class PluginRegistrar {
public:
	PluginRegistrar(Plugin& plugin);
};

#endif
