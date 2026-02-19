#ifndef COMBO_PLUGIN_HPP
#define COMBO_PLUGIN_HPP

#include "Adafruit_SH110X.h"
#include "Arduino.h"

#include "Color.hpp"
#include "Plugin.hpp"
#include "PluginEnvironment.hpp"

struct KeyDefinition {
	char     displayName[8];
	uint16_t keys[8];
	Color    color;
	uint16_t consumerKey;
};

struct LayerDefinition {
	char          displayName[8];
	KeyDefinition keyDefinitions[12];
};

struct EncoderKeyDefinition {
	uint16_t keys[6];
	uint16_t consumerKey;
};

struct EncoderDefinition {
	char                 displayName[16];
	EncoderKeyDefinition encoderKeys[2];
};

struct ComboPluginDefinition {
	char name[16];
	char displayName[16];

	KeyDefinition     keyDefinitions[12];
	LayerDefinition   layerDefinitions[12];
	EncoderDefinition encoderDefinitions[12];
};

class ComboPlugin: public Plugin {
public:
	ComboPlugin(PluginEnvironment& environment, const ComboPluginDefinition& definition);

	virtual void onActivate() override;

	virtual void onKeyDown(uint8_t key) override;
	virtual void onKeyUp(uint8_t key) override;
	virtual void onEncoderUp(int32_t count) override;
	virtual void onEncoderDown(int32_t count) override;

	virtual const char* getName() const override;

protected:
	PluginEnvironment&           _environment;
	const ComboPluginDefinition& _definition;

	uint8_t layerKey {0};
	int8_t  encoderMode {0};
	uint8_t displayMode {0};
};


#endif
