#include "TableView.h"
#include "Client.h"
#include "GameModel.h"
#include "Macros.h"
#include "Stats.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <fstream>
#include <thread>
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

using json = nlohmann::json;

TableView::TableView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/TableView.PNG")), client(this->gameModel.getClient()), gameState(this->gameModel.getGameState()) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	this->gameModel.getAudio().stopMusic();
	isRunning = true;
	isSendClicked = false;
	std::thread sendThread(&TableView::send, this);
	sendThread.detach();

	// Initialize widgets
	dialogPanel = tgui::Panel::create();
	dialogTextArea = tgui::TextArea::create();
	dearLabel = Widgets::Labels::createLabel("Dear Mom,", 30, 0, 0);
	letterTextArea = tgui::TextArea::create();
	buttonLayout = tgui::VerticalLayout::create({ 240, 220 });
	cancelButton = tgui::Button::create("CANCEL WRITING");
	sendButton = tgui::Button::create("SEND LETTER");

	dialogPanel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	dialogPanel->setSize(1920, 1080);
	dialogPanel->setVisible(false);
	dialogTextArea->setReadOnly();
	dialogTextArea->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::Transparent);
	dialogTextArea->getRenderer()->setSelectedTextColor(Macros::Colors::Redwood);
	dialogTextArea->getRenderer()->setCaretColor(tgui::Color::Transparent);
	dialogTextArea->setSize(1200, 300);
	dialogTextArea->setTextSize(30);
	dialogTextArea->getRenderer()->setBackgroundColor(Macros::Colors::TransparentGrey);
	dialogTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(dialogTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(dialogTextArea) - 50);
	dearLabel->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea) - 40);
	letterTextArea->setSize(730, 647);
	letterTextArea->setTextSize(30);
	letterTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea));
	letterTextArea->setMaximumCharacters(1500);
	buttonLayout->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayout->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(buttonLayout), tgui::bindHeight(gui) - tgui::bindHeight(buttonLayout));

	dialogPanel->onClick([=] {
		dialogPanel->setVisible(false);
	});
	cancelButton->onClick([=] {
		letterTextArea->setReadOnly();
		cancelButton->setEnabled(false);
		sendButton->setEnabled(false);
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});
	sendButton->onClick([=] {
		this->isSendClicked = true;
	});
	
	mainPanel->add(dearLabel);
	mainPanel->add(letterTextArea);
	mainPanel->add(buttonLayout);
	mainPanel->add(dialogPanel);
	dialogPanel->add(dialogTextArea);
	buttonLayout->add(cancelButton);
	buttonLayout->add(sendButton);
}

TableView::~TableView() {
	isRunning = false;
}

void TableView::send() {
	while(isRunning) {
		if(isSendClicked) {
			std::string textAreaText = letterTextArea->getText().toStdString();

			if(textAreaText.length() == 0) { // No input
				dialogTextArea->setText("What would Mom think if I sent an empty letter?");
				dialogPanel->setVisible(true);
			} else if(textAreaText.length() < 10) { // Input contains less than 10 characters
				dialogTextArea->setText("What would Mom think if I sent a letter with such few characters?");
				dialogPanel->setVisible(true);
			} else if(textAreaText.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?!()&\"':;/@#$%-\n ") != std::string::npos) { // Input contains characters that are not part of "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?!()&\"':;/@#$%-\n "
				dialogTextArea->setText("What would Mom think if I sent a letter that contains unusual characters?");
				dialogPanel->setVisible(true);
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
						viewController->changeView(ViewController::ViewType::MAIN_MENU_VIEW);
						break;
					}
				}

				std::string text = res["candidates"][0]["content"]["parts"][0]["text"];
				json parsedText = json::parse(text);

				// Update checkpoint
				gameState.updateCheckpoint();

				// Update stats
				gameState.updateCurrentStats(parsedText["stats"]);
				Stats stats = gameState.getCurrentStats();
				std::cout << "STATS: " << std::endl << "familyRelationship: " << stats.familyRelationship << std::endl << "mentalWellbeing: " << stats.mentalWellbeing << std::endl << "patriotism: " << stats.patriotism << std::endl << std::endl; // Log new stats

				// Update chat history
				std::string letter = parsedText["letter"];
				json newRes;
				newRes["role"] = "model";
				newRes["parts"][0]["text"] = letter;
				tempChatHistory.push_back(newRes);
				gameState.setChatHistory(tempChatHistory);

				gameState.save();
				viewController->changeView(ViewController::ViewType::SCENE_VIEW);
			}

			isSendClicked = false;
		}
	}
}