#include "ReadLetterView.h"
#include "GameModel.h"
#include "Macros.h"
#include "View.h"
#include "ViewController.h"
#include <nlohmann/json.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

using json = nlohmann::json;

ReadLetterView::ReadLetterView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, "Assets/Textures/Backgrounds/ReadLetterView.PNG"), gameState(this->gameModel.getGameState()) {
	tgui::Gui& gui = this->gameModel.getGui();

	// Initialize widgets
	letterTextArea = tgui::TextArea::create();
	finishButton = tgui::Button::create("FINISH READING");

	{
		std::vector<json> chatHistory = gameState.getChatHistory();
		json j = chatHistory.at(chatHistory.size() - 1);
		letterTextArea->setText(j["parts"][0]["text"].dump());
	}
	letterTextArea->setReadOnly();
	letterTextArea->setSize(822, 995);
	letterTextArea->setTextSize(30);
	letterTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f + 25, (tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea)) / 2.0f - 8);
	letterTextArea->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::Transparent);
	letterTextArea->getRenderer()->setSelectedTextColor(Macros::Colors::Redwood);
	letterTextArea->getRenderer()->setCaretColor(tgui::Color::Transparent);
	finishButton->setSize(240, 100);
	finishButton->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(finishButton), tgui::bindHeight(gui) - tgui::bindHeight(finishButton));

	finishButton->onClick([=] {
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});

	mainPanel->add(letterTextArea);
	mainPanel->add(finishButton);
}