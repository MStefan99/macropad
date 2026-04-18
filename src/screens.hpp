#ifndef SCREENS_HPP
#define SCREENS_HPP

#define ALLOW_STORAGE

#include "Plugin.hpp"


extern Plugin* mainScreen;
extern Plugin* appsScreen;
extern Plugin* settingsScreen;
extern Plugin* brightnessScreen;
extern Plugin* speedScreen;
extern Plugin* soundScreen;
extern Plugin* timeoutScreen;

extern uint8_t getActivePluginCount();
void           populateAppsScreen();

#endif
