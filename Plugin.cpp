#include "Plugin.hpp"

Plugin::Plugin(PluginEnvironment& environment):
  _environment {environment} {
	// Nothing to do
}

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

void Plugin::onTick() {
	// Empty stub
}

const char* Plugin::getName() const {
	return "plugin";
}

const char* Plugin::getDisplayName() const {
	return "Plugin";
}

const uint8_t* Plugin::getIcon() const {
	return nullptr;
}
