#include "QuickPlugin.hpp"

QuickPlugin::QuickPlugin(PluginEnvironment& environment, const QuickPluginDefinition& definition):
  Plugin {},
  _environment {environment},
  _definition {definition} {
	// Nothing to do
}

void QuickPlugin::onKeyDown(uint8_t key) {
	_environment.keyDispatcher.dispatch(_definition.keyDefinitions[key].keys);
}

void QuickPlugin::onEncoderDown(int32_t count) {
	_environment.keyDispatcher.dispatch(_definition.encoderDefinitions[0].keys);
}

void QuickPlugin::onEncoderUp(int32_t count) {
	_environment.keyDispatcher.dispatch(_definition.encoderDefinitions[1].keys);
}
