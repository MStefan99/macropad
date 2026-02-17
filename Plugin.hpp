#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include "Arduino.h"

#include "PluginEnvironment.hpp"

class Plugin {
protected:
	virtual ~Plugin() = 0;

public:
	static Plugin& create(const PluginEnvironment& environment);

	virtual void onKeyDown(uint8_t key) = 0;
	virtual void onKeyUp(uint8_t key) = 0;
	virtual void onEncoderUp(int32_t count);
	virtual void onEncoderDown(int32_t count);

	// Should return true if plugin did some work during the tick for optimal scheduling
	virtual bool onTick();
};

#endif
