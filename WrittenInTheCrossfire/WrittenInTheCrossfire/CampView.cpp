#include "CampView.h"
#include "Client.h"
#include "GameModel.h"
#include "Macros.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <fstream>
#include <thread>
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

CampView::CampView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/CampView.PNG")), client(this->gameModel.getClient()), gameState(this->gameModel.getGameState()) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	this->gameModel.getAudio().stopMusic();
	isRunning = true;
	isDontWriteClicked = false;
	std::thread dontWriteThread(&CampView::dontWrite, this);
	dontWriteThread.detach();

	// Initialize widgets
    buttonLayoutOne = tgui::HorizontalLayout::create({ 500, 100 });
    writeButton = tgui::Button::create("WRITE A LETTER");
	dontWriteButton = tgui::Button::create("DON'T WRITE A LETTER");
	buttonLayoutTwo = tgui::VerticalLayout::create({ 240, 220 });
    cancelButton = tgui::Button::create("CANCEL");
	selectButton = tgui::Button::create("SELECT");
	
    buttonLayoutOne->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayoutOne->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(buttonLayoutOne) + 20) / 2.0f, (tgui::bindHeight(gui) - tgui::bindHeight(buttonLayoutOne)) / 2.0f);
    buttonLayoutTwo->getRenderer()->setSpaceBetweenWidgets(20);
    buttonLayoutTwo->setVisible(false);

	writeButton->onClick([=] {
		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		this->viewController->changeView(ViewController::ViewType::TABLE_VIEW);
	});
	dontWriteButton->onClick([=] {
		writeButton->setEnabled(false);
		dontWriteButton->setEnabled(false);
		this->isDontWriteClicked = true;
	});

	mainPanel->add(buttonLayoutOne);
	mainPanel->add(buttonLayoutTwo);
	buttonLayoutOne->add(writeButton);
	buttonLayoutOne->add(dontWriteButton);
	buttonLayoutTwo->add(cancelButton);
	buttonLayoutTwo->add(selectButton);
}

CampView::~CampView() {
	isRunning = false;
}

void CampView::dontWrite() {
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

			viewController->changeView(ViewController::ViewType::SCENE_VIEW);
			isDontWriteClicked = false;
		}
	}
}