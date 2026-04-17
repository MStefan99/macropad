#ifndef SERIAL_PROVIDER_HPP
#define SERIAL_PROVIDER_HPP


#include "Arduino.h"

class SerialProvider {
public:
	using CallbackType = void (*)(const char* string);

	SerialProvider(CallbackType printCallback = nullptr);

	void print(const char* string);

protected:
	CallbackType _printCallback {};
};


#endif
