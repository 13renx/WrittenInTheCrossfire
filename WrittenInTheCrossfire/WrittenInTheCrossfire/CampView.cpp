#include "CampView.h"
#include "Client.h"
#include "GameModel.h"
#include "Macros.h"
#include "Utils.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <memory>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

using json = nlohmann::json;

CampView::CampView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/CampView.PNG")), client(this->gameModel.getClient()), gameState(this->gameModel.getGameState()) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	this->gameModel.getAudio().stopMusic();
	isRunning = true;
	isPicFrameFar = false;
	isDontWriteClicked = false;
	std::thread dontWriteThread(&CampView::dontWrite, this);
	dontWriteThread.detach();

	// Initialize widgets
    buttonLayoutOne = tgui::HorizontalLayout::create({ 500, 100 });
    writeButton = tgui::Button::create("WRITE A LETTER");
	dontWriteButton = tgui::Button::create("DON'T WRITE A LETTER");
	patriotismPanel = tgui::Panel::create();
	familyRelationshipGroup = tgui::Group::create();
	familyRelationshipPanel = tgui::Panel::create();
	familyRelationshipBackgroundPanel = tgui::Panel::create();
	mentalWellbeingPanel = tgui::Panel::create();
	//buttonLayoutTwo = tgui::VerticalLayout::create({ 240, 220 });
	//cancelButton = tgui::Button::create("CANCEL");
	//selectButton = tgui::Button::create("SELECT");

	mentalWellbeingPanel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	{
		Stats stats = gameState.getCurrentStats();

		// Patriotism
		if(stats.patriotism > 75) {
			patriotismPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Patriotism/Very Good.png");
		} else if(stats.patriotism > 50) {
			patriotismPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Patriotism/Good.png");
		} else if(stats.patriotism > 25) {
			patriotismPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Patriotism/Bad.png");
		} else if(stats.patriotism < 26) {
			patriotismPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Patriotism/Worse.png");
		}

		// Family Relationship
		if(stats.familyRelationship > 75) {
			familyRelationshipPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Family Relationship/Very Good.png");
		} else if(stats.familyRelationship > 50) {
			familyRelationshipPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Family Relationship/Good.png");
		} else if(stats.familyRelationship > 25) {
			familyRelationshipPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Family Relationship/Bad.png");
		} else if(stats.familyRelationship < 26) {
			familyRelationshipPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Family Relationship/Worse.png");
		}

		// Mental Wellbeing
		if(stats.mentalWellbeing > 50 && stats.mentalWellbeing < 76) {
			mentalWellbeingPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Mental Wellbeing/Good.png");
		} else if(stats.mentalWellbeing > 25 && stats.mentalWellbeing < 51) {
			mentalWellbeingPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Mental Wellbeing/Bad.png");
		} else if(stats.mentalWellbeing < 26) {
			mentalWellbeingPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Mental Wellbeing/Worse.png");
		}
	}
    buttonLayoutOne->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayoutOne->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(buttonLayoutOne) + 20) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(buttonLayoutOne)) / 2.0f);
	familyRelationshipBackgroundPanel->setVisible(false);
	familyRelationshipPanel->setScale(0.5f);
	familyRelationshipPanel->setPosition(70, 460);
	
    //buttonLayoutTwo->getRenderer()->setSpaceBetweenWidgets(20);
    //buttonLayoutTwo->setVisible(false);

	familyRelationshipBackgroundPanel->onClick([=, &gui] {
		Utils::Log::info("familyRelationshipBackgroundPanel clicked");

		if(!this->isPicFrameFar) {
			familyRelationshipBackgroundPanel->setVisible(false);
			familyRelationshipPanel->setPosition(70, 460);
		}
	});
	familyRelationshipPanel->onClick([=, &gui] {
		Utils::Log::info("familyRelationshipPanel clicked");

		if(this->isPicFrameFar) {
			familyRelationshipBackgroundPanel->setVisible(true);
			familyRelationshipPanel->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(familyRelationshipPanel) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(familyRelationshipPanel)) / 2.0f);
		} else {
			familyRelationshipBackgroundPanel->setVisible(false);
			familyRelationshipPanel->setPosition(70, 460);
		}
	});
	writeButton->onClick([=] {
		Utils::Log::info("writeButton clicked");

		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		this->viewController->changeView(ViewController::ViewType::WRITE_LETTER_VIEW);
	});
	dontWriteButton->onClick([=] {
		Utils::Log::info("dontWriteButton clicked");

		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		this->isDontWriteClicked = true;
	});
	
	mainPanel->add(familyRelationshipGroup);
	mainPanel->add(mentalWellbeingPanel);
	mainPanel->add(buttonLayoutOne);
	familyRelationshipGroup->add(familyRelationshipBackgroundPanel);
	familyRelationshipGroup->add(familyRelationshipPanel);
	//mainPanel->add(buttonLayoutTwo);
	buttonLayoutOne->add(writeButton);
	buttonLayoutOne->add(dontWriteButton);
	//buttonLayoutTwo->add(cancelButton);
	//buttonLayoutTwo->add(selectButton);
}

CampView::~CampView() {
	isRunning = false;
}

void CampView::dontWrite() {
	bool isGetFailed = false;

	while(isRunning) {
		if(isDontWriteClicked) {
			auto prompt = json::parse(R"(
				{
					"role": "user",
					"parts": [
						{
							"text": "NO_LETTER_SENT"
						}
					]
				}
			)");

			std::vector<json> tempChatHistory = gameState.getChatHistory();
			tempChatHistory.push_back(prompt);
			client.setGamePromptContents(tempChatHistory);

			json res = client.fetchResponse(Client::PromptType::GAME, client.getApiKey());
			std::cout << "RES: " << res.dump(4) << std::endl << std::endl; // Log LLM response

			// Error handling
			if(res.contains("error")) {
				res = client.fetchResponse(Client::PromptType::GAME, client.getApiKey());
				std::cout << "RES: " << res.dump(4) << std::endl << std::endl;

				if(res.contains("error")) {
					alertLabel->setText("API key is not working.");
					alertChildWindow->setVisible(true);
					isGetFailed = true;
					break;
				}
			}

			std::string text = res["candidates"][0]["content"]["parts"][0]["text"];
			json parsedText = json::parse(text);

			// Update stats
			gameState.updateCurrentStats(parsedText["stats"]);
			Stats& stats = gameState.getCurrentStats();
			std::cout << "STATS: " << std::endl << "familyRelationship: " << stats.familyRelationship << std::endl << "mentalWellbeing: " << stats.mentalWellbeing << std::endl << "patriotism: " << stats.patriotism << std::endl << std::endl; // Log new stats

			// Update checkpoint
			if(stats.mentalWellbeing < 1) {
				gameState.setCheckpoint(-1);
			}
			else if(stats.familyRelationship < 1) {
				gameState.setCheckpoint(-2);
			}
			else if(stats.patriotism < 1) {
				gameState.setCheckpoint(-3);
			} else {
				gameState.updateCheckpoint();
			}

			// Update chat history
			std::string letter = parsedText["letter"];
			json newRes;
			newRes["role"] = "model";
			newRes["parts"][0]["text"] = letter;
			tempChatHistory.push_back(newRes);
			gameState.setChatHistory(tempChatHistory);
			break;
		}
	}

	if(isGetFailed) {
		viewController->changeView(ViewController::ViewType::MAIN_MENU_VIEW);
	} else if(isDontWriteClicked) {
		viewController->changeView(ViewController::ViewType::SCENE_VIEW);
	}
}