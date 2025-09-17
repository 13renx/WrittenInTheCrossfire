#include "MenuView.h"
#include "Macros.h"
#include "SettingsView.h"
#include "View.h"
#include <fstream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>


MenuView::MenuView(tgui::Gui& g, std::shared_ptr<View> v) : View(g, v) {
	tgui::Theme::setDefault("Assets/Themes/Test.txt");

	mainPanel = tgui::Panel::create();
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

	mainPanel->getRenderer()->setTextureBackground("Assets/Textures/Backgrounds/Main Menu.PNG");
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

	newGameLabel->onMouseEnter([=]() { 
		newGameLabel->getRenderer()->setTextColor(tgui::Color::White);
	});
	newGameLabel->onMouseLeave([=]() { 
		newGameLabel->getRenderer()->setTextColor(Macros::Colors::Redwood);
	});
	settingsLabel->onClick([=]() { 
		gui.removeAllWidgets();
		activeView = std::make_shared<SettingsView>(gui, activeView);
	});
	exitLabel->onClick([=]() { exitGroup->setVisible(true); });
	exitPanel->onClick([=]() { exitGroup->setVisible(false); });
	exitMessageBox->onButtonPress([=](const tgui::String& button) {
		if(button == "YES") {
			exit(0);
		}
		else {
			exitGroup->setVisible(false);
		}
	});

	layout->add(newGameLabel);
	layout->add(continueLabel);
	layout->add(settingsLabel);
	layout->add(aboutLabel);
	layout->add(exitLabel);
	mainPanel->add(titleLabel);
	mainPanel->add(layout);
	exitGroup->add(exitPanel);
	exitGroup->add(exitMessageBox);
	mainPanel->add(exitGroup);
	gui.add(mainPanel);
}