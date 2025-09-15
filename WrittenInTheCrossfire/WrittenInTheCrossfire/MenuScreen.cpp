#include "Screen.h"
#include "MenuScreen.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MenuScreen::MenuScreen() {
	layout = tgui::GrowVerticalLayout::create();
	titleLabel = tgui::Label::create("Written in the Crossfire");
	newGameLabel = tgui::Label::create("NEW GAME");
	continueLabel = tgui::Label::create("CONTINUE");
	settingsLabel = tgui::Label::create("SETTINGS");
	aboutLabel = tgui::Label::create("ABOUT");
	exitLabel = tgui::Label::create("EXIT");

	titleLabel->setPosition(700, 100);
	titleLabel->setTextSize(100);
	layout->setPosition(1700, 500);

	layout->add(newGameLabel);
	layout->add(continueLabel);
	layout->add(settingsLabel);
	layout->add(aboutLabel);
	layout->add(exitLabel);
	panel->add(titleLabel);
	panel->add(layout);
}