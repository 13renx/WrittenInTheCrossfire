#include "WriteLetterView.h"
#include "Client.h"
#include "Fonts.h"
#include "GameModel.h"
#include "Macros.h"
#include "Utils.h"
#include "Stats.h"
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

WriteLetterView::WriteLetterView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, "Assets/Textures/Backgrounds/WriteLetterView.PNG"), client(this->gameModel.getClient()), gameState(this->gameModel.getGameState()) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	Fonts& fonts = this->gameModel.getFonts();
	Stats& stats = gameState.getCurrentStats();
	this->gameModel.getAudio().stopMusic();
	isPicFrameFar = true;
	isSendClicked = false;
	isRunning = true;
	std::thread sendThread(&WriteLetterView::send, this);
	sendThread.detach();

	// Initialize widgets
	dialogPanel = tgui::Panel::create();
	dialogTextArea = tgui::TextArea::create();
	dearLabel = Widgets::Labels::createLabel("Dear Mom,", 30, 0, 0, fonts.getWriting());
	letterTextArea = tgui::TextArea::create();
	familyRelationshipGroup = tgui::Group::create();
	familyRelationshipPicture = Widgets::Pictures::createPictureButton(window);
	familyRelationshipPanel = tgui::Panel::create();
	mentalWellbeingPicture = tgui::Picture::create();
	buttonLayout = tgui::VerticalLayout::create({ 240, 220 });
	cancelButton = tgui::Button::create("CANCEL WRITING");
	sendButton = tgui::Button::create("SEND LETTER");

	// Family Relationship
	if(stats.familyRelationship > 75) {
		familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Very Good.png");
	} else if(stats.familyRelationship > 50) {
		familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Good.png");
	} else if(stats.familyRelationship > 25) {
		familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Bad.png");
	} else if(stats.familyRelationship < 26) {
		familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Worse.png");
	}
	// Mental Wellbeing
	if(stats.mentalWellbeing > 50 && stats.mentalWellbeing < 76) {
		mentalWellbeingPicture->getRenderer()->setTexture("Assets/Textures/Backgrounds/Mental Wellbeing/Good.png");
	} else if(stats.mentalWellbeing > 25 && stats.mentalWellbeing < 51) {
		mentalWellbeingPicture->getRenderer()->setTexture("Assets/Textures/Backgrounds/Mental Wellbeing/Bad.png");
	} else if(stats.mentalWellbeing < 26) {
		mentalWellbeingPicture->getRenderer()->setTexture("Assets/Textures/Backgrounds/Mental Wellbeing/Worse.png");
	}
	familyRelationshipPanel->setVisible(false);
	dialogPanel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	dialogPanel->setSize(1920, 1080);
	dialogPanel->setVisible(false);
	dialogTextArea->setReadOnly();
	dialogTextArea->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::Transparent);
	dialogTextArea->getRenderer()->setSelectedTextColor(Macros::Colors::Redwood);
	dialogTextArea->getRenderer()->setCaretColor(tgui::Color::Transparent);
	dialogTextArea->setSize(1200, 300);
	dialogTextArea->setTextSize(30);
	dialogTextArea->getRenderer()->setTextColor(tgui::Color::White);
	dialogTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(dialogTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(dialogTextArea) - 50);
	dearLabel->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f + 46, tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea) - 90);
	dearLabel->getRenderer()->setTextColor(tgui::Color::Black);
	letterTextArea->setSize(822, 900);
	letterTextArea->setTextSize(30);
	letterTextArea->getRenderer()->setTextColor(tgui::Color::Black);
	letterTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f + 26, (tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea)) / 2.0f + 40);
	letterTextArea->setMaximumCharacters(1500);
	letterTextArea->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	letterTextArea->getRenderer()->setFont(fonts.getWriting());
	buttonLayout->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayout->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(buttonLayout), tgui::bindHeight(gui) - tgui::bindHeight(buttonLayout));

	familyRelationshipPanel->onClick([=, &gui, &stats] {
		Utils::Log::info("familyRelationshipPanel clicked");

		if(!this->isPicFrameFar) {
			familyRelationshipGroup->moveToBack();
			familyRelationshipPanel->setVisible(false);
			cancelButton->setVisible(true);
			sendButton->setVisible(true);
			familyRelationshipPicture->setSize(560, 516);
			familyRelationshipPicture->setPosition(0, 0);

			if(stats.familyRelationship > 75) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Very Good.png");
			} else if(stats.familyRelationship > 50) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Good.png");
			} else if(stats.familyRelationship > 25) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Bad.png");
			} else if(stats.familyRelationship < 26) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Worse.png");
			}

			this->isPicFrameFar = true;
		}
	});
	familyRelationshipPicture->onClick([=, &gui, &stats] {
		Utils::Log::info("familyRelationshipPicture clicked");

		if(this->isPicFrameFar) {
			familyRelationshipGroup->moveToFront();
			familyRelationshipPanel->setVisible(true);
			cancelButton->setVisible(false);
			sendButton->setVisible(false);
			familyRelationshipPicture->setSize(1920, 1080);

			// Family Relationship
			if(stats.familyRelationship > 75) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Near/Very Good.png");
			} else if(stats.familyRelationship > 50) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Near/Good.png");
			} else if(stats.familyRelationship > 25) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Near/Bad.png");
			} else if(stats.familyRelationship < 26) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Near/Worse.png");
			}

			this->isPicFrameFar = false;
		} else {
			familyRelationshipGroup->moveToBack();
			familyRelationshipPanel->setVisible(false);
			cancelButton->setVisible(true);
			sendButton->setVisible(true);
			familyRelationshipPicture->setSize(560, 516);

			if(stats.familyRelationship > 75) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Very Good.png");
			} else if(stats.familyRelationship > 50) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Good.png");
			} else if(stats.familyRelationship > 25) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Bad.png");
			} else if(stats.familyRelationship < 26) {
				familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Interactables/Family Relationship/Far/Worse.png");
			}

			familyRelationshipPicture->setPosition(0, 0);
			this->isPicFrameFar = true;
		}
	});
	dialogPanel->onClick([=] {
		Utils::Log::info("dialogPanel clicked");
		dialogPanel->setVisible(false);
	});
	cancelButton->onClick([=] {
		Utils::Log::info("cancelButton clicked");
		letterTextArea->setReadOnly();
		cancelButton->setEnabled(false);
		sendButton->setEnabled(false);
		this->gameModel.getAudio().stopSfx("paper");
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});
	sendButton->onClick([=] {
		Utils::Log::info("sendButton clicked");
		letterTextArea->setReadOnly();
		cancelButton->setEnabled(false);
		sendButton->setEnabled(false);
		this->isSendClicked = true;
	});

	mainPanel->add(familyRelationshipGroup);
	mainPanel->add(mentalWellbeingPicture);
	mainPanel->add(dearLabel);
	mainPanel->add(letterTextArea);
	mainPanel->add(buttonLayout);
	mainPanel->add(dialogPanel);
	familyRelationshipGroup->add(familyRelationshipPanel);
	familyRelationshipGroup->add(familyRelationshipPicture);
	dialogPanel->add(dialogTextArea);
	buttonLayout->add(cancelButton);
	buttonLayout->add(sendButton);

	this->gameModel.getAudio().playSfx("paper");
}

WriteLetterView::~WriteLetterView() {
	isRunning = false;
}

void WriteLetterView::send() {
	bool isGetFailed = false;

	while(isRunning) {
		if(isSendClicked) {
			std::string textAreaText = letterTextArea->getText().toStdString();
			std::string tempText = "";
			bool encounteredFirstNonSpace = false; // space and new line
			size_t spaceCtr = 0;

			// Removes extra whitespaces
			for(int i = 0; i < textAreaText.size(); i++) {
				if(encounteredFirstNonSpace) {
					if(textAreaText.at(i) == ' ' || textAreaText.at(i) == '\n') {
						if(spaceCtr == 0) {
							tempText.push_back(textAreaText.at(i));
						}

						spaceCtr++;
					} else {
						tempText.push_back(textAreaText.at(i));
						spaceCtr = 0;
					}
				} else if(textAreaText.at(i) != ' ' || textAreaText.at(i) != '\n') {
					encounteredFirstNonSpace = true;
					tempText.push_back(textAreaText.at(i));
				}
			}

			if(tempText.size() > 0) {
				if(tempText.at(tempText.size() - 1) == ' ' || tempText.at(tempText.size() - 1) == '\n') {
					tempText.pop_back();
				}
			}

			textAreaText = tempText;

			if(textAreaText.length() == 0) { // No input
				dialogTextArea->setText("What would Mom think if I sent an empty letter?");
				dialogPanel->setVisible(true);
				letterTextArea->setReadOnly(false);
				cancelButton->setEnabled(true);
				sendButton->setEnabled(true);
				isSendClicked = false;
				continue;
			} else if(textAreaText.length() < 10) { // Input contains less than 10 characters
				dialogTextArea->setText("What would Mom think if I sent a letter with such few characters?");
				dialogPanel->setVisible(true);
				letterTextArea->setReadOnly(false);
				cancelButton->setEnabled(true);
				sendButton->setEnabled(true);
				isSendClicked = false;
				continue;
			} else if(textAreaText.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?!()&\"':;/@#$%-\n ") != std::string::npos) { // Input contains characters that are not part of "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?!()&\"':;/@#$%-\n "
				dialogTextArea->setText("What would Mom think if I sent a letter that contains unusual characters?");
				dialogPanel->setVisible(true);
				letterTextArea->setReadOnly(false);
				cancelButton->setEnabled(true);
				sendButton->setEnabled(true);
				isSendClicked = false;
				continue;
			} else {
				auto prompt = json::parse(R"(
					{
						"role": "user",
						"parts": []
					}
				)");
				prompt["parts"][0]["text"] = fmt::format("Dear Mom,\n{}", textAreaText);

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

				gameState.save();
				break;
			}
		}
	}

	if(isGetFailed) {
		viewController->changeView(ViewController::ViewType::MAIN_MENU_VIEW);
	} else if(isSendClicked) {
		viewController->changeView(ViewController::ViewType::SCENE_VIEW);
	}
}