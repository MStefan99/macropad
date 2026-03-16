#ifndef OPTION_SCREEN_HPP
#define OPTION_SCREEN_HPP

#include "Arduino.h"

#include "Navigator.hpp"
#include "Plugin.hpp"

class OptionScreen: public Plugin {
public:
	using InitialCallback = bool (*)();
	using ChangeCallback = void  (*)(bool value);

	struct Definition {
		char            name[16];
		char            displayName[24];
		char            shortDisplayName[8];
		InitialCallback initialCallback;
		ChangeCallback  changeCallback;
		const uint32_t* icon;
	};

	OptionScreen(PluginEnvironment& environment, const Definition& definition);

	virtual void onActivate() override;
	virtual void onResume() override;

	virtual void onKeyUp(uint8_t key) override;

	virtual const char*     getName() const override;
	virtual const char*     getDisplayName() const override;
	virtual const char*     getShortDisplayName() const override;
	virtual const uint32_t* getIcon() const override;

protected:
	const Definition& _definition;
	uint8_t           _value {0};

	void _display();
};

#endif
