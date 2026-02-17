#ifndef QUICK_PLUGIN_HPP
#define QUICK_PLUGIN_HPP

#include "Arduino.h"

#include "Plugin.hpp"
#include "PluginEnvironment.hpp"

struct KeyDefinition {
	char    displayName[16];
	uint8_t keys[8];
};

struct EncoderDefinition {
	char    displayName[16];
	uint8_t keys[8];
};

struct QuickPluginDefinition {
	char              name[16];
	char              displayName[16];
	KeyDefinition     keyDefinitions[12];
	EncoderDefinition encoderDefinitions[2];
};

class QuickPlugin: public Plugin {
public:
	QuickPlugin(PluginEnvironment& environment, const QuickPluginDefinition& definition);

	virtual void onKeyDown(uint8_t key) override;
	virtual void onEncoderUp(int32_t count) override;
	virtual void onEncoderDown(int32_t count) override;

    virtual const char* getName() const override;

protected:
	PluginEnvironment&           _environment;
	const QuickPluginDefinition& _definition;
};

#endif
