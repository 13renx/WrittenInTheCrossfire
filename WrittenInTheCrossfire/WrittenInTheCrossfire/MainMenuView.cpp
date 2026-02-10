#include "MainMenuView.h"
#include "Client.h"
#include "Fonts.h"
#include "GameModel.h"
#include "GameState.h"
#include "Macros.h"
#include "Utils.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <fstream>
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

// Undefine the Windows API MessageBox macro which conflicts with tgui::MessageBox
#ifdef MessageBox
#undef MessageBox
#endif

MainMenuView::MainMenuView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/MainMenuView.PNG")) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	Fonts& fonts = this->gameModel.getFonts();
	Client& client = this->gameModel.getClient();
	GameState& gameState = this->gameModel.getGameState();
	this->gameModel.getAudio().playMusic();
	isContinueClicked = false;
	
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
	titleLabel = Widgets::Labels::createLabel("Written in the Crossfire", 80, 700, 180, fonts.getTitle());
	titleLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
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
	exitMessageBox->getRenderer()->setTextColor(tgui::Color::White);
	apiGroup->setVisible(false);
	apiChildWindow->setSize(400, 155);
	apiChildWindow->setPositionLocked(true);
	apiChildWindow->setTitleButtons(tgui::ChildWindow::TitleButton::None);
	apiChildWindow->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(apiChildWindow)) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(apiChildWindow)) / 2.0f);
	apiLabel->getRenderer()->setTextColor(tgui::Color::White);
	apiMainLayout->getRenderer()->setSpaceBetweenWidgets(15);
	apiMainLayout->getRenderer()->setPadding(20);
	apiEditBox->setMaximumCharacters(39);
	apiEditBox->setPasswordCharacter('*');
	apiButtonsLayout->setSize(0, 25);
	apiButtonsLayout->getRenderer()->setSpaceBetweenWidgets(20);
	apiFillerGroup->setSize(170, 0);
	optionsLayout->setPosition(1570, 500);
	{
		std::ifstream file = std::ifstream("game.json");

		if(!file.is_open()) {
			optionsContinueLabel->setEnabled(false);
			optionsContinueLabel->getRenderer()->setTextColor(Macros::Colors::Grey);
		}
	}
	
	exitPanel->onClick([=] { 
		Utils::Log::info("exitPanel clicked");
		exitGroup->setVisible(false); 
	});
	exitMessageBox->onButtonPress([=](const tgui::String& button) {//, &gameModel](const tgui::String& button) {
		if(button == "YES") {
			Utils::Log::info("exitMessageBox YES button clicked");
			//gameModel.getWindow().close();
			exit(0);
		}
		else {
			Utils::Log::info("exitMessageBox NO button clicked");
			exitGroup->setVisible(false);
		}
	});
	apiPanel->onClick([=] { 
		Utils::Log::info("apiPanel clicked");
		apiGroup->setVisible(false); 
	});
	apiCancelButton->onPress([=] { 
		Utils::Log::info("apiCancelButton clicked");
		apiGroup->setVisible(false);
	});
	apiEditBox->onMouseEnter([=, &window] {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Text));
	});
	apiEditBox->onMouseLeave([=, &window]() {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
	});
	apiEnterButton->onPress([=, &client, &gameState]() {
		Utils::Log::info("apiEnterButton clicked");
		const std::string apiKey = apiEditBox->getText().toStdString();
		
		if(apiKey != "") {
			auto [result, message] = client.testApiKey(apiKey);

			if(result) {
				client.setApiKey(apiKey);
				alertLabel->setText("API key stored successfully.");
				alertChildWindow->setVisible(true);

				if(isContinueClicked) {
					auto [result, message] = gameState.load();

					alertLabel->setText(message);
					alertChildWindow->setVisible(true);

					if(!result) {
						optionsContinueLabel->setEnabled(false);
						optionsContinueLabel->getRenderer()->setTextColor(Macros::Colors::Grey);
					} else {
						this->viewController->changeView(ViewController::ViewType::SCENE_VIEW);
						return;
					}
				} else {
					this->viewController->changeView(ViewController::ViewType::SCENE_VIEW);
					return;
				}
			} else {
				alertLabel->setText(message);
			}
		} else {
			alertLabel->setText("The input field is empty. Please enter an API key.");
		}

		alertChildWindow->setVisible(true);
	});
	optionsNewGameLabel->onClick([=, &window, &client, &gameState] { 
		isContinueClicked = false;
		Utils::Log::info("optionsNewGameLabel clicked");
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));

		if(client.getApiKey() == "") {
			apiGroup->setVisible(true);
		} else {
			auto[result, message] = client.testApiKey(client.getApiKey());

			alertLabel->setText(message);
			alertChildWindow->setVisible(true);

			if(result) {
				gameState.init();
				this->viewController->changeView(ViewController::ViewType::SCENE_VIEW);
			} else {
				apiGroup->setVisible(true);
			}
		}
	});
	optionsContinueLabel->onClick([=, &window, &client, &gameState] {
		isContinueClicked = true;
		Utils::Log::info("optionsContinueLabel clicked");
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
				} else { // Enter a new API key
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
		Utils::Log::info("optionsSettingsLabel clicked");
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewController->changeView(ViewController::ViewType::SETTINGS_VIEW);
	});
	optionsAboutLabel->onClick([=, &window] {
		Utils::Log::info("optionsAboutLabel clicked");
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewController->changeView(ViewController::ViewType::ABOUT_VIEW);
	});
	optionsExitLabel->onClick([=, &window] { 
		Utils::Log::info("optionsExitLabel clicked");
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