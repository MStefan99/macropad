#include "Plugin.hpp"

void Plugin::onEnable() {
  // Emtpy stub
}

void Plugin::onDisable() {
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

const char* Plugin::getLabelL() const {
  return "";
}

const char* Plugin::getLabelR() const {
  return "";
}
