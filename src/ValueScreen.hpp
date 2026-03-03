#ifndef VALUE_SCREEN_HPP
#define VALUE_SCREEN_HPP

#include "Arduino.h"

#include "Navigator.hpp"
#include "Plugin.hpp"

class ValueScreen: public Plugin {
public:
	using InitialCallback = int (*)();
	using ChangeCallback = void (*)(int value);

	struct Limits {
		int minValue;
		int maxValue;
		int step;
	};

	struct Definition {
		char            name[16];
		char            displayName[16];
		Limits          limits;
		InitialCallback initialCallback;
		ChangeCallback  changeCallback;
		const uint32_t* icon;
	};

	ValueScreen(PluginEnvironment& environment, const Definition& definition);

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
	int               _value {0};

	void _display();

	void _decrement();
	void _increment();
};

#endif
