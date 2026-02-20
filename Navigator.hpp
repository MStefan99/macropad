#ifndef NAVIGATOR_HPP
#define NAVIGATOR_HPP


#include "Arduino.h"

#include "Plugin.hpp"

class Navigator {
public:
	using OpenCallbackType = void  (*)(Plugin* plugin);
	using CloseCallbackType = void (*)();

	Navigator(OpenCallbackType open, CloseCallbackType close);

	void open(Plugin* plugin);
	void close();

protected:
	OpenCallbackType  _openCallback {};
	CloseCallbackType _closeCallback {};
};

#endif
