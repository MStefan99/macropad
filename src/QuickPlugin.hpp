#ifndef QUICK_PLUGIN_HPP
#define QUICK_PLUGIN_HPP


#include "Arduino.h"

#include "Color.hpp"
#include "Plugin.hpp"
#include "PluginEnvironment.hpp"

class QuickPlugin: public Plugin {
public:
	struct KeyDefinition {
		char displayName[8];

		struct {
			uint8_t  keys[8];
			uint16_t consumerKey;
		};

		Color color;
	};

	struct EncoderKeyDefinition {
		uint8_t  keys[8];
		uint16_t consumerKey;
	};

	struct EncoderDefinition {
		char                 displayName[16];
		EncoderKeyDefinition encoderKeys[2];
		EncoderKeyDefinition encoderPushKeys;
	};

	struct Definition {
		char              name[16];
		char              displayName[24];
		char              shortDisplayName[8];
		KeyDefinition     keyDefinitions[12];
		EncoderDefinition encoderDefinition;
		const uint32_t*   icon;
	};

	QuickPlugin(PluginEnvironment& environment, const Definition& definition);

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
	const Definition& _definition;

	void _highlight(uint8_t key, bool down = false);
};


#endif
