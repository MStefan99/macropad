#ifndef LIST_SCREEN_HPP
#define LIST_SCREEN_HPP


#include "Arduino.h"

#include "Navigator.hpp"
#include "Plugin.hpp"

class ListScreen: public Plugin {
public:
	using ListItemCallback = void (*)();

	struct ListScreenItem {
		char             displayName[16];
		ListItemCallback callback;
		const uint8_t*   icon;
	};

	struct Definition {
		char           name[16];
		char           displayName[16];
		ListScreenItem items[16];
	};

	ListScreen(PluginEnvironment& environment, const Definition& definition);

	virtual void onActivate() override;

	virtual void onKeyDown(uint8_t key) override;
	virtual void onKeyUp(uint8_t key) override;
	virtual void onEncoderDown(int32_t count) override;
	virtual void onEncoderUp(int32_t count) override;

	virtual const char* getName() const override;
	virtual const char* getDisplayName() const override;

protected:
	const Definition& _definition;
	uint8_t           _activeItem {0};
	uint8_t           _leftItem {0};

	void _displayItems();

	void _prevItem();
	void _nextItem();
};

#endif
