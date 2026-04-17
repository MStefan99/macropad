#include "SerialProvider.hpp"

SerialProvider::SerialProvider(CallbackType printCallback):
  _printCallback {printCallback} {
	// Nothing to do
}

void SerialProvider::print(const char* string) {
	if (_printCallback) {
		_printCallback(string);
	}
}
