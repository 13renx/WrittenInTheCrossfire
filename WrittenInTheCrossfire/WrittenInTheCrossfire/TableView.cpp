#include "TableView.h"
#include "Client.h"
#include "GameModel.h"
#include "Stats.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <fstream>
#include <thread>
#include <memory>
#include <Windows.h>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

using json = nlohmann::json;

TableView::TableView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, tgui::Texture::Texture("Assets/Textures/Backgrounds/TableView.PNG")), client(this->gameModel.getClient()), gameStateModel(this->gameModel.getGameStateModel()) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	isSendClicked = false;
	std::thread sendThread(&TableView::send, this);
	sendThread.detach();

	// Initialize widgets
	dearLabel = Widgets::Labels::createLabel("Dear Mom,", 30, 0, 0);
	letterTextArea = tgui::TextArea::create();
	buttonLayout = tgui::VerticalLayout::create({ 240, 220 });
	cancelButton = tgui::Button::create("CANCEL WRITING");
	sendButton = tgui::Button::create("SEND LETTER");

	dearLabel->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea) - 40);
	letterTextArea->setSize(730, 647);
	letterTextArea->setTextSize(30);
	letterTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea));
	letterTextArea->setMaximumCharacters(1500);
	buttonLayout->getRenderer()->setSpaceBetweenWidgets(20);
	buttonLayout->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(buttonLayout), tgui::bindHeight(gui) - tgui::bindHeight(buttonLayout));

	cancelButton->onClick([=, &window] {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});
	sendButton->onClick([=] {
		this->isSendClicked = true;
	});
	 
	mainPanel->add(dearLabel);
	mainPanel->add(letterTextArea);
	mainPanel->add(buttonLayout);
	buttonLayout->add(cancelButton);
	buttonLayout->add(sendButton);
}

void TableView::send() {
	while(true) {
		if(isSendClicked) {
			auto prompt = json::parse(R"(
				{
					"role": "user",
					"parts": []
				}
			)");
			prompt["parts"][0]["text"] = fmt::format("Dear Mom,\n{}", letterTextArea->getText().toStdString());
			std::vector<json> tempChatHistory = gameStateModel.getChatHistory();
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
					this->viewController->changeView(ViewController::ViewType::MENU_VIEW);
					break;
				}
			}

			std::string text = res["candidates"][0]["content"]["parts"][0]["text"];
			json parsedText = json::parse(text);

			// Update stats
			gameStateModel.updateCurrentStats(parsedText["stats"]);
			Stats stats = gameStateModel.getCurrentStats();
			std::cout << "STATS: " << std::endl << "familyRelationship: " << stats.familyRelationship << std::endl << "mentalWellbeing: " << stats.mentalWellbeing << std::endl << "patriotism: " << stats.patriotism << std::endl << std::endl; // Log new stats

			// Update chat history
			std::string letter = parsedText["letter"];
			json newRes;
			newRes["role"] = "model";
			newRes["parts"][0]["text"] = letter;
			tempChatHistory.push_back(newRes);
			gameStateModel.setChatHistory(tempChatHistory);

			isSendClicked = false;
			this->viewController->changeView(ViewController::ViewType::SCENE_VIEW);
			break;
		}
	}
}