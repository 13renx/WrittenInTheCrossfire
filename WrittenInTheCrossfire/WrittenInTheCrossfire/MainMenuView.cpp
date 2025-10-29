#include "MainMenuView.h"
#include "Client.h"
#include "GameModel.h"
#include "GameState.h"
#include "Macros.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <fstream>
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

MainMenuView::MainMenuView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/Main Menu.PNG")) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	Client& client = this->gameModel.getClient();
	GameState& gameState = this->gameModel.getGameState();
	this->gameModel.getAudio().playMusic();
	
	// Initialize widgets
	exitGroup = tgui::Group::create();
	exitMessageBox = tgui::MessageBox::create("", "ARE YOU SURE YOU WANT TO EXIT?", { "NO", "YES" });
	exitPanel = tgui::Panel::create();
	apiGroup = tgui::Group::create();
	apiChildWindow = tgui::ChildWindow::create();
	apiPanel = tgui::Panel::create();
	apiMainLayout = tgui::GrowVerticalLayout::create();
	apiButtonsLayout = tgui::GrowHorizontalLayout::create();
	apiLabel = Widgets::Labels::createLabel("ENTER GEMINI API KEY", 13, 0, 0);
	apiEditBox = tgui::EditBox::create();
	apiFillerGroup = tgui::Group::create();
	apiEnterButton = tgui::Button::create("ENTER");
	apiCancelButton = tgui::Button::create("CANCEL");
	titleLabel = Widgets::Labels::createLabel("Written in the Crossfire", 100, 700, 100);
	optionsLayout = tgui::GrowVerticalLayout::create();
	optionsNewGameLabel = Widgets::Labels::createButtonLabel("NEW GAME", 50, 0, 0, window);
	optionsContinueLabel = Widgets::Labels::createButtonLabel("CONTINUE", 50, 0, 0, window);
	optionsSettingsLabel = Widgets::Labels::createButtonLabel("SETTINGS", 50, 0, 0, window);
	optionsAboutLabel = Widgets::Labels::createButtonLabel("ABOUT", 50, 0, 0, window);
	optionsExitLabel = Widgets::Labels::createButtonLabel("EXIT", 50, 0, 0, window);

	exitGroup->setVisible(false);
	exitMessageBox->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(exitMessageBox)) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(exitMessageBox)) / 2.0f);
	exitMessageBox->setButtonAlignment(tgui::HorizontalAlignment::Right);
	exitMessageBox->setPositionLocked(true);
	exitPanel->getRenderer()->setOpacity(0.5f);
	apiGroup->setVisible(false);
	apiChildWindow->setSize(400, 155);
	apiChildWindow->setPositionLocked(true);
	apiChildWindow->setTitleButtons(tgui::ChildWindow::TitleButton::None);
	apiChildWindow->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(apiChildWindow)) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(apiChildWindow)) / 2.0f);
	apiPanel->getRenderer()->setOpacity(0.5f);
	apiMainLayout->getRenderer()->setSpaceBetweenWidgets(15);
	apiMainLayout->getRenderer()->setPadding(20);
	apiEditBox->setMaximumCharacters(39);
	apiButtonsLayout->setSize(0, 25);
	apiButtonsLayout->getRenderer()->setSpaceBetweenWidgets(20);
	apiFillerGroup->setSize(190, 0);
	optionsLayout->setPosition(1570, 500);
	{
		std::ifstream file = std::ifstream("game.json");

		if(!file.is_open()) {
			optionsContinueLabel->setEnabled(false);
			optionsContinueLabel->getRenderer()->setTextColor(Macros::Colors::Grey);
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
	apiPanel->onClick([=] { apiGroup->setVisible(false); });
	apiCancelButton->onPress([=] { apiGroup->setVisible(false); });
	apiEnterButton->onPress([=, &client]() { 
		const std::string apiKey = apiEditBox->getText().toStdString();
		
		if(apiKey != "") {
			auto [result, message] = client.testApiKey(apiKey);

			if(result) {
				client.setApiKey(apiKey);
				apiGroup->setVisible(false);
				alertLabel->setText("API key stored successfully.");
			}
			else {
				alertLabel->setText(message);
			}
		} else {
			alertLabel->setText("The input field is empty. Please enter an API key.");
		}

		alertChildWindow->setVisible(true);
	});
	optionsNewGameLabel->onClick([=, &window, &client] { 
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));

		if(client.getApiKey() == "") {
			apiGroup->setVisible(true);
		} else {
			auto[result, message] = client.testApiKey(client.getApiKey());

			alertLabel->setText(message);
			alertChildWindow->setVisible(true);

			if(result) {
				this->viewController->changeView(ViewController::ViewType::SCENE_VIEW);
			} else {
				apiGroup->setVisible(true);
			}
		}
	});
	optionsContinueLabel->onClick([=, &window, &client, &gameState] {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));

		if(client.getApiKey() == "") {
			apiGroup->setVisible(true);
		} else {
			auto [result, message] = gameState.load();

			if(result) {
				auto [result, message] = client.testApiKey(client.getApiKey());

				alertLabel->setText(message);
				alertChildWindow->setVisible(true);

				if(result) {
					this->viewController->changeView(ViewController::ViewType::SCENE_VIEW);
				} else {
					apiGroup->setVisible(true);
				}
			} else {
				alertLabel->setText(message);
				alertChildWindow->setVisible(true);
				optionsContinueLabel->setEnabled(false);
				optionsContinueLabel->getRenderer()->setTextColor(Macros::Colors::Grey);
			}
		}
	});
	optionsSettingsLabel->onClick([=, &window] {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewController->changeView(ViewController::ViewType::SETTINGS_VIEW);
	});
	optionsAboutLabel->onClick([=, &window] {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewController->changeView(ViewController::ViewType::ABOUT_VIEW);
	});
	optionsExitLabel->onClick([=, &window] { 
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		exitGroup->setVisible(true); 
	});

	mainPanel->add(titleLabel);
	mainPanel->add(optionsLayout);
	mainPanel->add(exitGroup);
	mainPanel->add(apiGroup);
	exitGroup->add(exitPanel);
	exitGroup->add(exitMessageBox);
	apiGroup->add(apiPanel);
	apiGroup->add(apiChildWindow);
	apiChildWindow->add(apiMainLayout);
	apiMainLayout->add(apiLabel);
	apiMainLayout->add(apiEditBox);
	apiMainLayout->add(apiButtonsLayout);
	apiButtonsLayout->add(apiFillerGroup);
	apiButtonsLayout->add(apiEnterButton);
	apiButtonsLayout->add(apiCancelButton);
	optionsLayout->add(optionsNewGameLabel);
	optionsLayout->add(optionsContinueLabel);
	//optionsLayout->add(optionsSettingsLabel);
	optionsLayout->add(optionsAboutLabel);
	optionsLayout->add(optionsExitLabel);
}