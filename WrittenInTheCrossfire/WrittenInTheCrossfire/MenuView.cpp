#include "MenuView.h"
#include "Macros.h"
#include "SettingsView.h"
#include "View.h"
#include "Widgets.h"
#include <memory>
#include <typeinfo>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MenuView::MenuView(tgui::Gui& gui, std::shared_ptr<View> activeView) : View(activeView) {
	sf::Window* window = gui.getWindow();

	mainPanel = Widgets::Panels::createPanel("Assets/Textures/Backgrounds/Main Menu.PNG");
	titleLabel = Widgets::Labels::createLabel("Written in the Crossfire", 100, 700, 100);
	optionsLayout = tgui::GrowVerticalLayout::create();
	newGameLabel = Widgets::Labels::createButtonLabel("NEW GAME", 50, 0, 0, window);
	continueLabel = Widgets::Labels::createButtonLabel("CONTINUE", 50, 0, 0, window);
	settingsLabel = Widgets::Labels::createButtonLabel("SETTINGS", 50, 0, 0, window);
	aboutLabel = Widgets::Labels::createButtonLabel("ABOUT", 50, 0, 0, window);
	exitLabel = Widgets::Labels::createButtonLabel("EXIT", 50, 0, 0, window);
	exitGroup = tgui::Group::create();
	exitMessageBox = tgui::MessageBox::create("", "ARE YOU SURE YOU WANT TO EXIT?", { "YES", "NO" });
	exitPanel = tgui::Panel::create();

	optionsLayout->setPosition(1570, 500);
	exitGroup->setVisible(false);
	exitMessageBox->setPosition(760, 400);
	exitPanel->getRenderer()->setOpacity(0.5f);
	std::shared_ptr<View> v;
	settingsLabel->onClick([=, &gui] {
		gui.removeAllWidgets();
		std::shared_ptr<View> settingsView = std::make_shared<SettingsView>(gui, nullptr);
		this->activeView = settingsView;
		settingsView->setActiveView(this->activeView);

	});
	exitLabel->onClick([=] { exitGroup->setVisible(true); });
	exitPanel->onClick([=] { exitGroup->setVisible(false); });
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