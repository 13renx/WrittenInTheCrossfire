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
	isPicFrameFar = true;
	isDontWriteClicked = false;
	std::thread dontWriteThread(&CampView::dontWrite, this);
	dontWriteThread.detach();

	// Initialize widgets
    buttonLayoutOne = tgui::HorizontalLayout::create({ 500, 100 });
    writeButton = tgui::Button::create("WRITE A LETTER");
	dontWriteButton = tgui::Button::create("DON'T WRITE A LETTER");
	exitTentButton = tgui::Button::create("EXIT TENT");
	patriotismPicture = tgui::Picture::create();
	familyRelationshipGroup = tgui::Group::create();
	familyRelationshipPicture = Widgets::Pictures::createPictureButton(window);
	familyRelationshipPanel = tgui::Panel::create();
	newspaperGroup = tgui::Group::create();
	newspaperPicture = Widgets::Pictures::createPictureButton(window, tgui::Texture::Texture("Assets/Textures/Diegetic Interface/Newspaper/Not Holding.PNG"));
	newspaperPanel = tgui::Panel::create();
	handMirrorGroup = tgui::Group::create();
	handMirrorPicture = Widgets::Pictures::createPictureButton(window, tgui::Texture::Texture("Assets/Textures/Diegetic Interface/Hand Mirror/Not Holding.PNG"));
	handMirrorPanel = tgui::Panel::create();
	mentalWellbeingPicture = tgui::Picture::create();
	
	//buttonLayoutTwo = tgui::VerticalLayout::create({ 240, 220 });
	//cancelButton = tgui::Button::create("CANCEL");
	//selectButton = tgui::Button::create("SELECT");

	{
		Stats stats = gameState.getCurrentStats();

		// Patriotism
		if(stats.patriotism > 75) {
			patriotismPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Patriotism/Very Good.png");
		} else if(stats.patriotism > 50) {
			patriotismPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Patriotism/Good.png");
		} else if(stats.patriotism > 25) {
			patriotismPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Patriotism/Bad.png");
		} else if(stats.patriotism < 26) {
			patriotismPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Patriotism/Worse.png");
		}

		// Family Relationship
		if(stats.familyRelationship > 75) {
			familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Family Relationship/Very Good.png");
		} else if(stats.familyRelationship > 50) {
			familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Family Relationship/Good.png");
		} else if(stats.familyRelationship > 25) {
			familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Family Relationship/Bad.png");
		} else if(stats.familyRelationship < 26) {
			familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Family Relationship/Worse.png");
		}

		// Mental Wellbeing
		if(stats.mentalWellbeing > 50 && stats.mentalWellbeing < 76) {
			mentalWellbeingPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Mental Wellbeing/Good.png");
		} else if(stats.mentalWellbeing > 25 && stats.mentalWellbeing < 51) {
			mentalWellbeingPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Mental Wellbeing/Bad.png");
		} else if(stats.mentalWellbeing < 26) {
			mentalWellbeingPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Mental Wellbeing/Worse.png");
		}
	}
    buttonLayoutOne->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayoutOne->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(buttonLayoutOne) + 20) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(buttonLayoutOne)) / 2.0f);
	exitTentButton->setSize(240, 100);
	exitTentButton->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(exitTentButton), tgui::bindHeight(gui) - tgui::bindHeight(exitTentButton));
	mentalWellbeingPicture->setIgnoreMouseEvents(true);
	familyRelationshipPanel->setVisible(false);
	familyRelationshipPanel->getRenderer()->setBackgroundColor(Macros::Colors::TransparentGrey);
	familyRelationshipPicture->setScale(0.5f);
	familyRelationshipPicture->setPosition(70, 460);
	newspaperPanel->setVisible(false);
	newspaperPanel->getRenderer()->setBackgroundColor(Macros::Colors::TransparentGrey);
	newspaperPicture->setScale(0.5f);
	newspaperPicture->setPosition(450, 630);
	handMirrorPanel->setVisible(false);
	handMirrorPanel->getRenderer()->setBackgroundColor(Macros::Colors::TransparentGrey);
	handMirrorPicture->setScale(0.5f);
	handMirrorPicture->setPosition(50, 860);
	
    //buttonLayoutTwo->getRenderer()->setSpaceBetweenWidgets(20);
    //buttonLayoutTwo->setVisible(false);

	familyRelationshipPanel->onClick([=, &gui] {
		Utils::Log::info("familyRelationshipPanel clicked");

		if(!this->isPicFrameFar) {
			familyRelationshipPanel->setVisible(false);
			familyRelationshipPicture->setScale(0.5f);
			familyRelationshipPicture->setPosition(70, 460);
			this->isPicFrameFar = true;
		}
	});
	familyRelationshipPicture->onClick([=, &gui] {
		Utils::Log::info("familyRelationshipPicture clicked");

		if(this->isPicFrameFar) {
			familyRelationshipPanel->setVisible(true);
			familyRelationshipPicture->setScale(1.5f);
			familyRelationshipPicture->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(familyRelationshipPanel) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(familyRelationshipPanel)) / 2.0f);
			this->isPicFrameFar = false;
		} else {
			familyRelationshipPanel->setVisible(false);
			familyRelationshipPicture->setScale(0.5f);
			familyRelationshipPicture->setPosition(70, 460);
			this->isPicFrameFar = true;
		}
	});
	newspaperPicture->onClick([=] {
		Utils::Log::info("newspaperPicture clicked");
	});
	handMirrorPicture->onClick([=] {
		Utils::Log::info("handMirrorPicture clicked");
	});
	writeButton->onClick([=] {
		Utils::Log::info("writeButton clicked");

		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		exitTentButton->setEnabled(false);
		this->viewController->changeView(ViewController::ViewType::WRITE_LETTER_VIEW);
	});
	dontWriteButton->onClick([=] {
		Utils::Log::info("dontWriteButton clicked");

		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		exitTentButton->setEnabled(false);
		this->isDontWriteClicked = true;
	});
	exitTentButton->onClick([=] {
		Utils::Log::info("dontWriteButton clicked");

		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		exitTentButton->setEnabled(false);
		this->viewController->changeView(ViewController::ViewType::MAP_VIEW);
	});
	
	mainPanel->add(familyRelationshipGroup);
	mainPanel->add(newspaperGroup);
	mainPanel->add(handMirrorGroup);
	mainPanel->add(mentalWellbeingPicture);
	mainPanel->add(buttonLayoutOne);
	mainPanel->add(exitTentButton);
	familyRelationshipGroup->add(familyRelationshipPanel);
	familyRelationshipGroup->add(familyRelationshipPicture);
	newspaperGroup->add(newspaperPanel);
	newspaperGroup->add(newspaperPicture);
	handMirrorGroup->add(handMirrorPanel);
	handMirrorGroup->add(handMirrorPicture);
	buttonLayoutOne->add(writeButton);
	buttonLayoutOne->add(dontWriteButton);
	//mainPanel->add(buttonLayoutTwo);
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
			} else if(stats.familyRelationship < 1) {
				gameState.setCheckpoint(-2);
			} else if(stats.patriotism < 1) {
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