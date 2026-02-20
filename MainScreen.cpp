#include "MainScreen.hpp"

MainScreen::MainScreen(ScreenEnvironment& environment):
  Plugin(environment) {
	// Nothing to do
}

void MainScreen::onActivate() {
	_activeItem = 0;

	_environment.canvas.fillScreen(SH110X_BLACK);
	_environment.canvas.setTextColor(SH110X_WHITE);
	_environment.canvas.print("Settings");
	_environment.canvas.display();
}

void MainScreen::onKeyDown(uint8_t key) {}

const char* MainScreen::getName() const {
	return "menu_m";
}

const char* MainScreen::getDisplayName() const {
	return "Options";
}
