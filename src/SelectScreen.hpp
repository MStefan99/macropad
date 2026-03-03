#ifndef SELECT_SCREEN_HPP
#define SELECT_SCREEN_HPP

#include "Arduino.h"

#include "Navigator.hpp"
#include "Plugin.hpp"

class SelectScreen: public Plugin {
public:
	using InitialCallback = int (*)();
	using ChangeCallback = void (*)(int value);

	struct Option {
		char displayName[16];
		int  value;
	};

	struct Definition {
		char            name[16];
		char            displayName[16];
		Option          options[16];
		InitialCallback initialCallback;
		ChangeCallback  changeCallback;
		const uint32_t* icon;
	};

	SelectScreen(PluginEnvironment& environment, const Definition& definition);

	virtual void onActivate() override;
	virtual void onResume() override;

	virtual void onKeyUp(uint8_t key) override;
	virtual void onEncoderDown(int32_t count) override;
	virtual void onEncoderUp(int32_t count) override;

	virtual const char*     getName() const override;
	virtual const char*     getDisplayName() const override;
	virtual const uint32_t* getIcon() const override;

protected:
	const Definition& _definition;
	uint8_t           _idx {0};

	void _display();

	void _prevItem();
	void _nextItem();
};

#endif
