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
	familyRelationshipPanel = tgui::Panel::create();
	mentalWellbeingPanel = tgui::Panel::create();
	
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
	{
		std::vector<json> chatHistory = gameState.getChatHistory();
		json j = chatHistory.at(chatHistory.size() - 1);
		letterTextArea->setText(j["parts"][0]["text"].dump());
	}
	letterTextArea->setReadOnly();
	letterTextArea->setSize(822, 995);
	letterTextArea->setTextSize(30);
	letterTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f + 26, (tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea)) / 2.0f - 8);
	letterTextArea->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::Transparent);
	letterTextArea->getRenderer()->setSelectedTextColor(Macros::Colors::Redwood);
	letterTextArea->getRenderer()->setCaretColor(tgui::Color::Transparent);
	letterTextArea->getRenderer()->setTextColor(tgui::Color::Black);
	finishButton->setSize(240, 100);
	finishButton->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(finishButton), tgui::bindHeight(gui) - tgui::bindHeight(finishButton));

	finishButton->onClick([=] {
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});

	mainPanel->add(familyRelationshipPanel);
	mainPanel->add(mentalWellbeingPanel);
	mainPanel->add(letterTextArea);
	mainPanel->add(finishButton);
}