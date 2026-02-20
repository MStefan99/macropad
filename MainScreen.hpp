#ifndef MAIN_SCREEN_HPP
#define MAIN_SCREEN_HPP


#include "Arduino.h"

#include "Plugin.hpp"

class MainScreen: public Plugin {
public:
	MainScreen(PluginEnvironment& environment);

	virtual void onActivate() override;

	virtual void onKeyDown(uint8_t key) override;

	virtual const char* getName() const override;
	virtual const char* getDisplayName() const override;

protected:
	uint8_t _activeItem {0};
};

#endif
