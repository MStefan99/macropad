#ifndef LIST_SCREEN_HPP
#define LIST_SCREEN_HPP


#include "Arduino.h"

#include "Navigator.hpp"
#include "Plugin.hpp"

class ListScreen: public Plugin {
public:
	using ListItemCallback = void (*)(uint8_t idx);

	struct ListScreenItem {
		char             displayName[8];
		ListItemCallback callback;
		const uint32_t*  icon;
	};

	struct Definition {
		char            name[16];
		char            displayName[24];
		char            shortDisplayName[8];
		ListScreenItem  items[16];
		uint8_t         firstItem {0};
		const uint32_t* icon;
	};

	ListScreen(PluginEnvironment& environment, const Definition& definition);

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
	const Definition& _definition;
	uint8_t           _activeItem {0};
	uint8_t           _leftItem {0};

	void _displayItems();

	void _prevItem();
	void _nextItem();
};

#endif
