#ifndef QUICK_PLUGIN_HPP
#define QUICK_PLUGIN_HPP

#include "Adafruit_SH110X.h"

#include "Arduino.h"

#include "Color.hpp"
#include "Plugin.hpp"
#include "PluginEnvironment.hpp"


struct KeyDefinition {
	char    displayName[16];
	uint16_t keys[8];
	Color color;
	uint16_t consumerKey;
};

struct EncoderKeyDefinition {
	uint16_t keys[6];
	uint16_t consumerKey;
};

struct EncoderDefinition {
	char    displayName[16];
	EncoderKeyDefinition encoderKeys[2];
};

struct QuickPluginDefinition {
	char              name[16];
	char              displayName[16];
	KeyDefinition     keyDefinitions[12];
	EncoderDefinition encoderDefinition;
};

class QuickPlugin: public Plugin {
public:
	QuickPlugin(PluginEnvironment& environment, const QuickPluginDefinition& definition);

	virtual void onActivate() override;

	virtual void onKeyDown(uint8_t key) override;
	virtual void onKeyUp(uint8_t key) override;
	virtual void onEncoderUp(int32_t count) override;
	virtual void onEncoderDown(int32_t count) override;

	virtual const char* getName() const override;

protected:
	PluginEnvironment&           _environment;
	const QuickPluginDefinition& _definition;

	void _highlight(uint8_t key, bool down);
};


#endif
