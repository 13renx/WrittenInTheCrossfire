#include "MenuView.h"
#include "Macros.h"
#include "SettingsView.h"
#include "View.h"
#include <fstream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MenuView::MenuView(tgui::Gui& g, std::shared_ptr<View> v) : View(g, v) {
	mainPanel = tgui::Panel::create();
	titleLabel = tgui::Label::create("Written in the Crossfire");
	optionsLayout = tgui::GrowVerticalLayout::create();
	newGameLabel = tgui::Label::create("NEW GAME");
	continueLabel = tgui::Label::create("CONTINUE");
	settingsLabel = tgui::Label::create("SETTINGS");
	aboutLabel = tgui::Label::create("ABOUT");
	exitLabel = tgui::Label::create("EXIT");
	exitGroup = tgui::Group::create();
	exitMessageBox = tgui::MessageBox::create("", "ARE YOU SURE YOU WANT TO EXIT?", { "YES", "NO" });
	exitPanel = tgui::Panel::create();

	mainPanel->getRenderer()->setTextureBackground("Assets/Textures/Backgrounds/Main Menu.PNG");
	titleLabel->setPosition(700, 100);
	titleLabel->setTextSize(100);
	optionsLayout->setPosition(1570, 500);
	newGameLabel->setTextSize(50);
	continueLabel->setTextSize(50);
	settingsLabel->setTextSize(50);
	aboutLabel->setTextSize(50);
	exitLabel->setTextSize(50);
	exitGroup->setVisible(false);
	exitMessageBox->setPosition(760, 400);
	exitPanel->getRenderer()->setOpacity(0.5f);
	
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

	mainPanel->add(titleLabel);
	mainPanel->add(optionsLayout);
	mainPanel->add(exitGroup);
	optionsLayout->add(newGameLabel);
	optionsLayout->add(continueLabel);
	optionsLayout->add(settingsLabel);
	optionsLayout->add(aboutLabel);
	optionsLayout->add(exitLabel);
	exitGroup->add(exitPanel);
	exitGroup->add(exitMessageBox);
	gui.add(mainPanel);
}