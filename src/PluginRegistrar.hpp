#ifndef PLUGIN_REGISTRAR_HPP
#define PLUGIN_REGISTRAR_HPP

#include "Plugin.hpp"

extern Plugin* plugins[];
extern uint8_t pluginCount;

class PluginRegistrar {
public:
	PluginRegistrar(Plugin& plugin);
};

#endif
