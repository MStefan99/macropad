#include "Plugin.hpp"

void Plugin::onActivate() {
	// Emtpy stub
}

void Plugin::onDeactivate() {
	// Empty stub
}

void Plugin::onKeyUp(uint8_t key) {
	// Empty stub
}

void Plugin::onEncoderDown(int32_t count) {
	// Empty stub
}

void Plugin::onEncoderUp(int32_t count) {
	// Empty stub
}

bool Plugin::onTick() {
	// Empty stub
	return false;
}

const char* Plugin::getName() const {
	return "Untitled";
}
