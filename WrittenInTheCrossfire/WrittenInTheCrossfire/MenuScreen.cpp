#include "MenuScreen.h"
#include "Screen.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MenuScreen::MenuScreen(tgui::Gui& g) : Screen(g) {
	layout = tgui::GrowVerticalLayout::create();
	titleLabel = tgui::Label::create("Written in the Crossfire");
	newGameLabel = tgui::Label::create("NEW GAME");
	continueLabel = tgui::Label::create("CONTINUE");
	settingsLabel = tgui::Label::create("SETTINGS");
	aboutLabel = tgui::Label::create("ABOUT");
	exitLabel = tgui::Label::create("EXIT");
	exitPanel = tgui::Panel::create();
	exitMessageBox = tgui::MessageBox::create("", "ARE YOU SURE YOU WANT TO EXIT?", { "YES", "NO" });
	exitGroup = tgui::Group::create();

	stylize();
	functionalize();

	layout->add(newGameLabel);
	layout->add(continueLabel);
	layout->add(settingsLabel);
	layout->add(aboutLabel);
	layout->add(exitLabel, "ExitLabel");
	panel->add(titleLabel);
	panel->add(layout);
	exitGroup->add(exitPanel);
	exitGroup->add(exitMessageBox);
	panel->add(exitGroup, "ExitGroup");
	gui.add(panel, "MenuScreen");
}

void MenuScreen::stylize() {
	layout->setPosition(1570, 500);
	titleLabel->setPosition(700, 100);
	titleLabel->setTextSize(100);
	newGameLabel->setTextSize(50);
	continueLabel->setTextSize(50);
	settingsLabel->setTextSize(50);
	aboutLabel->setTextSize(50);
	exitLabel->setTextSize(50);
	exitPanel->getRenderer()->setOpacity(0.5f);
	exitGroup->setVisible(false);
	exitMessageBox->setPosition(760, 400);
}

void MenuScreen::functionalize() {
	// New Game
	

	// Continue
	

	// Settings
	//settingsLabel->onClick([=]() { });

	// About
	//aboutLabel->onClick([=]() { });

	// Exit
	exitLabel->onClick([=]() { exitGroup->setVisible(true); });
	exitPanel->onClick([=]() { exitGroup->setVisible(false); });
	exitMessageBox->onButtonPress([=](const tgui::String& button) {
		if(button == "YES") {
			exit(0);
		} else {
			exitGroup->setVisible(false);
		}
	});
}