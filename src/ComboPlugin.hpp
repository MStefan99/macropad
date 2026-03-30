#ifndef COMBO_PLUGIN_HPP
#define COMBO_PLUGIN_HPP


#include "Arduino.h"

#include "Color.hpp"
#include "Plugin.hpp"
#include "PluginEnvironment.hpp"

class ComboPlugin: public Plugin {
public:
	struct KeyDefinition {
		char displayName[8];

		struct {
			uint8_t  keys[8];
			uint16_t consumerKey;
		};

		Color color;
	};

	struct LayerDefinition {
		char          displayName[10];
		KeyDefinition keyDefinitions[12];
		Color         color;
	};

	struct EncoderKeyDefinition {
		uint8_t  keys[8];
		uint16_t consumerKey;
	};

	struct EncoderDefinition {
		char                 displayName[10];
		EncoderKeyDefinition encoderKeys[2];
		Color                color;
	};

	struct Definition {
		char name[16];
		char displayName[24];
		char shortDisplayName[8];

		KeyDefinition     keyDefinitions[12];
		LayerDefinition   layerDefinitions[12];
		EncoderDefinition encoderDefinitions[12];
		const uint32_t*   icon;
	};

	ComboPlugin(PluginEnvironment& environment, const Definition& definition);

	virtual void onActivate() override;
	virtual void onResume() override;

	virtual void onKeyDown(uint8_t key) override;
	virtual void onKeyUp(uint8_t key) override;
	virtual void onEncoderDown(int32_t count) override;
	virtual void onEncoderUp(int32_t count) override;

	virtual const char*     getName() const override;
	virtual const char*     getDisplayName() const override;
	virtual const char*     getShortDisplayName() const override;
	virtual const uint32_t* getIcon() const override;

protected:
	enum class DisplayMode : uint8_t {
		KEY,
		LAYER,
		ENCODER
	};

	const Definition& _definition;

	uint8_t     _layerKey {0};
	bool        _comboActivated {false};
	int8_t      _encoderMode {0};
	DisplayMode _displayMode {DisplayMode::KEY};

	void _printLabel(uint8_t idx, const char* label);
	void _displayLayer();
	void _display(bool peek = false);
	void _highlight(uint8_t key, bool down = false);
};


#endif
