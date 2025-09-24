#include "MenuView.h"
#include "Macros.h"
#include "View.h"
#include "ViewManager.h"
#include "Widgets.h"
#include <fstream>
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MenuView::MenuView(tgui::Gui& gui, ViewManager* viewManager) : View(viewManager) {
	gameModel = GameModel();
	sf::Window* window = gui.getWindow();

	mainPanel = Widgets::Panels::createPanel("Assets/Textures/Backgrounds/Main Menu.PNG");
	exitGroup = tgui::Group::create();
	exitMessageBox = tgui::MessageBox::create("", "ARE YOU SURE YOU WANT TO EXIT?", { "NO", "YES" });
	exitPanel = tgui::Panel::create();
	apiChildWindow = tgui::ChildWindow::create();
	apiEditBox = tgui::EditBox::create();
	titleLabel = Widgets::Labels::createLabel("Written in the Crossfire", 100, 700, 100);
	optionsLayout = tgui::GrowVerticalLayout::create();
	newGameLabel = Widgets::Labels::createButtonLabel("NEW GAME", 50, 0, 0, window);
	continueLabel = Widgets::Labels::createButtonLabel("CONTINUE", 50, 0, 0, window);
	settingsLabel = Widgets::Labels::createButtonLabel("SETTINGS", 50, 0, 0, window);
	aboutLabel = Widgets::Labels::createButtonLabel("ABOUT", 50, 0, 0, window);
	exitLabel = Widgets::Labels::createButtonLabel("EXIT", 50, 0, 0, window);
	
	exitGroup->setVisible(false);
	exitMessageBox->setPosition(760, 400);
	exitMessageBox->setButtonAlignment(tgui::HorizontalAlignment::Right);
	exitPanel->getRenderer()->setOpacity(0.5f);
	apiChildWindow->add(apiEditBox);
	apiChildWindow->setSize(500, 300);
	optionsLayout->setPosition(1570, 500);
	{
		std::ifstream file = std::ifstream("game.json");

		if(!file.is_open()) {
			continueLabel->setEnabled(false);
			continueLabel->getRenderer()->setTextColor(Macros::Colors::Grey);
		}
	}
	
	exitPanel->onClick([=] { exitGroup->setVisible(false); });
	exitMessageBox->onButtonPress([=](const tgui::String& button) {
		if(button == "YES") {
			exit(0);
		}
		else {
			exitGroup->setVisible(false);
		}
	});
	newGameLabel->onClick([] {

	});
	settingsLabel->onClick([=, &gui] {
		window->setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewManager->changeView(ViewManager::ViewType::SETTINGS_VIEW);
	});
	exitLabel->onClick([=] { exitGroup->setVisible(true); });

	mainPanel->add(titleLabel);
	mainPanel->add(optionsLayout);
	mainPanel->add(exitGroup);
	mainPanel->add(apiChildWindow);
	exitGroup->add(exitPanel);
	exitGroup->add(exitMessageBox);
	optionsLayout->add(newGameLabel);
	optionsLayout->add(continueLabel);
	optionsLayout->add(settingsLabel);
	optionsLayout->add(aboutLabel);
	optionsLayout->add(exitLabel);
	gui.add(mainPanel);
}