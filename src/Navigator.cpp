#include "Navigator.hpp"

Navigator::Navigator(Navigator::OpenCallbackType openCallback, Navigator::CloseCallbackType closeCallback):
  _openCallback {openCallback},
  _closeCallback {closeCallback} {
	// Nothing to do
}

void Navigator::open(Plugin* plugin) {
	if (_openCallback) {
		_openCallback(plugin);
	}
}

void Navigator::close() {
	if (_closeCallback) {
		_closeCallback();
	}
}
