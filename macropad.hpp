#ifndef MACROPAD_HPP
#define MACROPAD_HPP

#define ALLOW_HARDWARE


#include "KeyDispatcher.hpp"
#include "Plugin.hpp"
#include "PluginBacklight.hpp"
#include "PluginCanvas.hpp"
#include "PluginEnvironment.hpp"
#include "PluginTone.hpp"


extern PluginCanvas      pluginCanvas;
extern PluginBacklight   pluginBacklight;
extern PluginTone        pluginTone;
extern KeyDispatcher     keyDispatcher;
extern PluginEnvironment pluginEnvironment;


extern Plugin* definedPlugins[];


#endif
