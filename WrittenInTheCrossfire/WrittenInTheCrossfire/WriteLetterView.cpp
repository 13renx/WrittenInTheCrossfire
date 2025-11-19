#include "WriteLetterView.h"
#include "Client.h"
#include "GameModel.h"
#include "Macros.h"
#include "Stats.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include "Fonts.h"
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
	this->gameModel.getAudio().stopMusic();
	isRunning = true;
	isSendClicked = false;
	std::thread sendThread(&WriteLetterView::send, this);
	sendThread.detach();

	// Initialize widgets
	dialogPanel = tgui::Panel::create();
	dialogTextArea = tgui::TextArea::create();
	dearLabel = Widgets::Labels::createLabel("Dear Mom,", 30, 0, 0, Fonts::Writing);
	letterTextArea = tgui::TextArea::create();
	familyRelationshipPanel = tgui::Panel::create();
	mentalWellbeingPanel = tgui::Panel::create();
	buttonLayout = tgui::VerticalLayout::create({ 240, 220 });
	cancelButton = tgui::Button::create("CANCEL WRITING");
	sendButton = tgui::Button::create("SEND LETTER");

	mentalWellbeingPanel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	{
		Stats stats = gameState.getCurrentStats();

		// Family Relationship
		if(stats.familyRelationship > 75) {
			familyRelationshipPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Family Relationship/Very Good.png");
		}
		else if(stats.familyRelationship > 50) {
			familyRelationshipPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Family Relationship/Good.png");
		}
		else if(stats.familyRelationship > 25) {
			familyRelationshipPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Family Relationship/Bad.png");
		}
		else if(stats.familyRelationship < 26) {
			familyRelationshipPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Family Relationship/Worse.png");
		}

		// Mental Wellbeing
		if(stats.mentalWellbeing > 50 && stats.mentalWellbeing < 76) {
			mentalWellbeingPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Mental Wellbeing/Good.png");
		}
		else if(stats.mentalWellbeing > 25 && stats.mentalWellbeing < 51) {
			mentalWellbeingPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Mental Wellbeing/Bad.png");
		}
		else if(stats.mentalWellbeing < 26) {
			mentalWellbeingPanel->getRenderer()->setTextureBackground("Assets/Textures/Diegetic Interface/Mental Wellbeing/Worse.png");
		}
	}
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
	dialogTextArea->getRenderer()->setBackgroundColor(Macros::Colors::TransparentGrey);
	dialogTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(dialogTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(dialogTextArea) - 50);
	dearLabel->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f + 30, tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea) - 90);
	dearLabel->getRenderer()->setTextColor(tgui::Color::Black);
	letterTextArea->setSize(822, 900);
	letterTextArea->setTextSize(30);
	letterTextArea->getRenderer()->setTextColor(tgui::Color::Black);
	letterTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f + 26, (tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea)) / 2.0f + 40);
	letterTextArea->setMaximumCharacters(1500);
	letterTextArea->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	letterTextArea->getRenderer()->setFont(Fonts::Writing);
	buttonLayout->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayout->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(buttonLayout), tgui::bindHeight(gui) - tgui::bindHeight(buttonLayout));

	dialogPanel->onClick([=] {
		dialogPanel->setVisible(false);
	});
	cancelButton->onClick([=] {
		letterTextArea->setReadOnly();
		cancelButton->setEnabled(false);
		sendButton->setEnabled(false);
		this->gameModel.getAudio().stopSfx("paper");
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});
	sendButton->onClick([=] {
		letterTextArea->setReadOnly();
		cancelButton->setEnabled(false);
		sendButton->setEnabled(false);
		this->isSendClicked = true;
	});

	mainPanel->add(familyRelationshipPanel);
	mainPanel->add(mentalWellbeingPanel);
	mainPanel->add(dearLabel);
	mainPanel->add(letterTextArea);
	mainPanel->add(buttonLayout);
	mainPanel->add(dialogPanel);
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
				if(stats.mentalWellbeing < 1) {
					gameState.setCheckpoint(-1);
				}
				else if(stats.familyRelationship < 1) {
					gameState.setCheckpoint(-2);
				}
				else if(stats.patriotism < 1) {
					gameState.setCheckpoint(-3);
				}
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
				}
				else {
					gameState.updateCheckpoint();
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