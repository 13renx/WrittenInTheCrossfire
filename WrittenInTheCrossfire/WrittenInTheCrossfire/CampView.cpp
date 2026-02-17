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

CampView::CampView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("./Assets/Textures/Backgrounds/CampView.PNG")), client(this->gameModel.getClient()), gameState(this->gameModel.getGameState()) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	Stats& stats = gameState.getCurrentStats();
	this->gameModel.getAudio().stopMusic();
	isPicFrameFar = true;
	isNewspaperFar = true;
	isHandMirrorFar = true;
	isDontWriteClicked = false;
	isRunning = true;
	std::thread dontWriteThread(&CampView::dontWrite, this);
	dontWriteThread.detach();

	// Initialize widgets
    buttonLayoutOne = tgui::HorizontalLayout::create({ 500, 100 });
    writeButton = tgui::Button::create("WRITE A LETTER");
	dontWriteButton = tgui::Button::create("DON'T WRITE A LETTER");
	exitTentButton = tgui::Button::create("EXIT TENT");
	patriotismPicture = tgui::Picture::create();
	interactableGroup = tgui::Group::create();
	familyRelationshipGroup = tgui::Group::create();
	familyRelationshipPicture = Widgets::Pictures::createPictureButton(window);
	familyRelationshipPanel = tgui::Panel::create();
	newspaperGroup = tgui::Group::create();
	newspaperPicture = Widgets::Pictures::createPictureButton(window, tgui::Texture::Texture("./Assets/Textures/Interactables/Newspaper/Far.PNG"));
	newspaperPanel = tgui::Panel::create();
	handMirrorGroup = tgui::Group::create();
	handMirrorPicture = Widgets::Pictures::createPictureButton(window, tgui::Texture::Texture("./Assets/Textures/Interactables/Hand Mirror/Far.PNG"));
	handMirrorPanel = tgui::Panel::create();
	mentalWellbeingPicture = tgui::Picture::create();
	
	//buttonLayoutTwo = tgui::VerticalLayout::create({ 240, 220 });
	//cancelButton = tgui::Button::create("CANCEL");
	//selectButton = tgui::Button::create("SELECT");

	// Patriotism
	if(stats.patriotism > 75) {
		patriotismPicture->getRenderer()->setTexture("./Assets/Textures/Backgrounds/Patriotism/Very Good.png");
	} else if(stats.patriotism > 50) {
		patriotismPicture->getRenderer()->setTexture("./Assets/Textures/Backgrounds/Patriotism/Good.png");
	} else if(stats.patriotism > 25) {
		patriotismPicture->getRenderer()->setTexture("./Assets/Textures/Backgrounds/Patriotism/Bad.png");
	} else if(stats.patriotism < 26) {
		patriotismPicture->getRenderer()->setTexture("./Assets/Textures/Backgrounds/Patriotism/Worse.png");
	}
	// Family Relationship
	if(stats.familyRelationship > 75) {
		familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Very Good.png");
	} else if(stats.familyRelationship > 50) {
		familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Good.png");
	} else if(stats.familyRelationship > 25) {
		familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Bad.png");
	} else if(stats.familyRelationship < 26) {
		familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Worse.png");
	}
	// Mental Wellbeing
	if(stats.mentalWellbeing > 50 && stats.mentalWellbeing < 76) {
		mentalWellbeingPicture->getRenderer()->setTexture("./Assets/Textures/Backgrounds/Mental Wellbeing/Good.png");
	} else if(stats.mentalWellbeing > 25 && stats.mentalWellbeing < 51) {
		mentalWellbeingPicture->getRenderer()->setTexture("./Assets/Textures/Backgrounds/Mental Wellbeing/Bad.png");
	} else if(stats.mentalWellbeing < 26) {
		mentalWellbeingPicture->getRenderer()->setTexture("./Assets/Textures/Backgrounds/Mental Wellbeing/Worse.png");
	}
    buttonLayoutOne->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayoutOne->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(buttonLayoutOne) + 20) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(buttonLayoutOne)) / 2.0f);
	exitTentButton->setSize(240, 100);
	exitTentButton->setPosition(1400, 300);
	mentalWellbeingPicture->setIgnoreMouseEvents(true);
	familyRelationshipPanel->setVisible(false);
	familyRelationshipPicture->setScale(0.5f);
	familyRelationshipPicture->setPosition(70, 460);
	newspaperPanel->setVisible(false);
	newspaperPicture->setScale(0.5f);
	newspaperPicture->setPosition(450, 630);
	handMirrorPanel->setVisible(false);
	handMirrorPicture->setScale(0.5f);
	handMirrorPicture->setPosition(50, 860);
	
    //buttonLayoutTwo->getRenderer()->setSpaceBetweenWidgets(20);
    //buttonLayoutTwo->setVisible(false);

	familyRelationshipPanel->onClick([=, &gui, &stats] {
		Utils::Log::debugInfo("familyRelationshipPanel clicked");

		if(!this->isPicFrameFar) {
			familyRelationshipGroup->moveToBack();
			familyRelationshipPanel->setVisible(false);
			buttonLayoutOne->setVisible(true);
			exitTentButton->setVisible(true);
			familyRelationshipPicture->setScale(0.5f);
			familyRelationshipPicture->setSize(560, 516);

			if(stats.familyRelationship > 75) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Very Good.png");
			} else if(stats.familyRelationship > 50) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Good.png");
			} else if(stats.familyRelationship > 25) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Bad.png");
			} else if(stats.familyRelationship < 26) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Worse.png");
			}

			familyRelationshipPicture->setPosition(70, 460);
			this->isPicFrameFar = true;
		}
	});
	familyRelationshipPicture->onClick([=, &gui, &stats] {
		Utils::Log::debugInfo("familyRelationshipPicture clicked");

		if(this->isPicFrameFar) {
			familyRelationshipGroup->moveToFront();
			familyRelationshipPanel->setVisible(true);
			buttonLayoutOne->setVisible(false);
			exitTentButton->setVisible(false);
			familyRelationshipPicture->setScale(1.0f);
			familyRelationshipPicture->setSize(1920, 1080);

			// Family Relationship
			if(stats.familyRelationship > 75) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Near/Very Good.png");
			} else if(stats.familyRelationship > 50) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Near/Good.png");
			} else if(stats.familyRelationship > 25) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Near/Bad.png");
			} else if(stats.familyRelationship < 26) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Near/Worse.png");
			}

			familyRelationshipPicture->setPosition(0, 0);
			this->isPicFrameFar = false;
		} else {
			familyRelationshipGroup->moveToBack();
			familyRelationshipPanel->setVisible(false);
			buttonLayoutOne->setVisible(true);
			exitTentButton->setVisible(true);
			familyRelationshipPicture->setScale(0.5f);
			familyRelationshipPicture->setSize(560, 516);

			if(stats.familyRelationship > 75) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Very Good.png");
			} else if(stats.familyRelationship > 50) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Good.png");
			} else if(stats.familyRelationship > 25) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Bad.png");
			} else if(stats.familyRelationship < 26) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Worse.png");
			}

			familyRelationshipPicture->setPosition(70, 460);
			this->isPicFrameFar = true;
		}
	});
	newspaperPanel->onClick([=, &gui] {
		Utils::Log::debugInfo("newspaperPanel clicked");

		if(!this->isNewspaperFar) {
			newspaperGroup->moveToBack();
			newspaperPanel->setVisible(false);
			buttonLayoutOne->setVisible(true);
			exitTentButton->setVisible(true);
			newspaperPicture->setScale(0.5f);
			newspaperPicture->setSize(500, 349);
			newspaperPicture->getRenderer()->setTexture(tgui::Texture::Texture("./Assets/Textures/Interactables/Newspaper/Far.PNG"));
			newspaperPicture->setPosition(450, 630);
			this->isNewspaperFar = true;
		}
	});
	newspaperPicture->onClick([=, &gui] {
		Utils::Log::debugInfo("newspaperPicture clicked");

		if(this->isNewspaperFar) {
			newspaperGroup->moveToFront();
			newspaperPanel->setVisible(true);
			buttonLayoutOne->setVisible(false);
			exitTentButton->setVisible(false);
			newspaperPicture->setScale(1.0f);
			newspaperPicture->setSize(1920, 1080);
			newspaperPicture->getRenderer()->setTexture(tgui::Texture::Texture("./Assets/Textures/Interactables/Newspaper/Near.PNG"));
			newspaperPicture->setPosition(0, 0);
			this->isNewspaperFar = false;
		} else {
			newspaperGroup->moveToBack();
			newspaperPanel->setVisible(false);
			buttonLayoutOne->setVisible(true);
			exitTentButton->setVisible(true);
			newspaperPicture->setScale(0.5f);
			newspaperPicture->setSize(500, 349);
			newspaperPicture->getRenderer()->setTexture(tgui::Texture::Texture("./Assets/Textures/Interactables/Newspaper/Far.PNG"));
			newspaperPicture->setPosition(450, 630);
			this->isNewspaperFar = true;
		}
	});
	handMirrorPanel->onClick([=] {
		Utils::Log::debugInfo("handMirrorPanel clicked");

		if(!this->isHandMirrorFar) {
			handMirrorGroup->moveToBack();
			handMirrorPanel->setVisible(false);
			buttonLayoutOne->setVisible(true);
			exitTentButton->setVisible(true);
			handMirrorPicture->setScale(0.5f);
			handMirrorPicture->setSize(500, 349);
			handMirrorPicture->getRenderer()->setTexture(tgui::Texture::Texture("./Assets/Textures/Interactables/Hand Mirror/Far.PNG"));
			handMirrorPicture->setPosition(50, 860);
			this->isHandMirrorFar = true;
		}
	});
	handMirrorPicture->onClick([=, &gui, &stats] {
		Utils::Log::debugInfo("handMirrorPicture clicked");

		if(this->isHandMirrorFar) {
			handMirrorGroup->moveToFront();
			handMirrorPanel->setVisible(true);
			buttonLayoutOne->setVisible(false);
			exitTentButton->setVisible(false);
			handMirrorPicture->setScale(1.0f);
			handMirrorPicture->setSize(1920, 1080);

			if(stats.mentalWellbeing > 75) {
				handMirrorPicture->getRenderer()->setTexture(tgui::Texture::Texture("./Assets/Textures/Interactables/Hand Mirror/Near/Very Good.png"));
			} else if(stats.mentalWellbeing > 50) {
				handMirrorPicture->getRenderer()->setTexture(tgui::Texture::Texture("./Assets/Textures/Interactables/Hand Mirror/Near/Good.png"));
			} else if(stats.mentalWellbeing > 25) {
				handMirrorPicture->getRenderer()->setTexture(tgui::Texture::Texture("./Assets/Textures/Interactables/Hand Mirror/Near/Bad.png"));
			} else if(stats.mentalWellbeing < 26) {
				handMirrorPicture->getRenderer()->setTexture(tgui::Texture::Texture("./Assets/Textures/Interactables/Hand Mirror/Near/Worse.png"));
			}
			
			handMirrorPicture->setPosition(0, 0);
			this->isHandMirrorFar = false;
		} else {
			handMirrorGroup->moveToBack();
			handMirrorPanel->setVisible(false);
			buttonLayoutOne->setVisible(true);
			exitTentButton->setVisible(true);
			handMirrorPicture->setScale(0.5f);
			handMirrorPicture->setSize(500, 349);
			handMirrorPicture->getRenderer()->setTexture(tgui::Texture::Texture("./Assets/Textures/Interactables/Hand Mirror/Far.PNG"));
			handMirrorPicture->setPosition(50, 860);
			this->isHandMirrorFar = true;
		}
	});
	writeButton->onClick([=] {
		Utils::Log::debugInfo("writeButton clicked");

		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		exitTentButton->setEnabled(false);
		this->viewController->changeView(ViewController::ViewType::WRITE_LETTER_VIEW);
	});
	dontWriteButton->onClick([=] {
		Utils::Log::debugInfo("dontWriteButton clicked");

		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		exitTentButton->setEnabled(false);
		this->isDontWriteClicked = true;
	});
	exitTentButton->onClick([=] {
		Utils::Log::debugInfo("dontWriteButton clicked");

		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		exitTentButton->setEnabled(false);
		this->viewController->changeView(ViewController::ViewType::MAP_VIEW);
	});
	
	mainPanel->add(patriotismPicture);
	mainPanel->add(interactableGroup);
	mainPanel->add(mentalWellbeingPicture);
	mainPanel->add(buttonLayoutOne);
	mainPanel->add(exitTentButton);
	interactableGroup->add(newspaperGroup);
	interactableGroup->add(familyRelationshipGroup);
	interactableGroup->add(handMirrorGroup);
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

			// Error handling
			if(res.contains("error")) {
				res = client.fetchResponse(Client::PromptType::GAME, client.getApiKey());

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

			// Update checkpoint
			if(stats.mentalWellbeing < 1) {
				gameState.setCheckpoint(-1);
			} else if(stats.familyRelationship < 1) {
				gameState.setCheckpoint(-2);
			} else if(stats.patriotism < 1) {
				gameState.setCheckpoint(-3);
			} else {
				gameState.incrementCheckpoint();
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
		viewController->changeView(ViewController::ViewType::MAIN_SCENE_VIEW);
	}
}