#include "Screen.h"
#include "MenuScreen.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MenuScreen::MenuScreen() {
	titleLabel = tgui::Label::create("Written In The Crossfire");
	newGameLabel = tgui::Label::create("New Game");
	continueLabel = tgui::Label::create("Continue");
	settingsLabel = tgui::Label::create("Settings");
	aboutLabel = tgui::Label::create("About");
	exitLabel = tgui::Label::create("Exit");

	panel->add(titleLabel);
	panel->add(newGameLabel);
	panel->add(continueLabel);
	panel->add(settingsLabel);
	panel->add(aboutLabel);
	panel->add(exitLabel);
}