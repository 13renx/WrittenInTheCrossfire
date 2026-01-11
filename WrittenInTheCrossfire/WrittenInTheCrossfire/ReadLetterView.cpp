#include "ReadLetterView.h"
#include "GameModel.h"
#include "Macros.h"
#include "Utils.h"
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
	familyRelationshipPicture = tgui::Picture::create();
	mentalWellbeingPicture = tgui::Picture::create();
	
	{
		Stats stats = gameState.getCurrentStats();

		// Family Relationship
		if(stats.familyRelationship > 75) {
			familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Family Relationship/Very Good.png");
		}
		else if(stats.familyRelationship > 50) {
			familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Family Relationship/Good.png");
		}
		else if(stats.familyRelationship > 25) {
			familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Family Relationship/Bad.png");
		}
		else if(stats.familyRelationship < 26) {
			familyRelationshipPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Family Relationship/Worse.png");
		}

		// Mental Wellbeing
		if(stats.mentalWellbeing > 50 && stats.mentalWellbeing < 76) {
			mentalWellbeingPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Mental Wellbeing/Good.png");
		}
		else if(stats.mentalWellbeing > 25 && stats.mentalWellbeing < 51) {
			mentalWellbeingPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Mental Wellbeing/Bad.png");
		}
		else if(stats.mentalWellbeing < 26) {
			mentalWellbeingPicture->getRenderer()->setTexture("Assets/Textures/Diegetic Interface/Mental Wellbeing/Worse.png");
		}
	}
	{
		std::vector<json> chatHistory = gameState.getChatHistory();
		json j = chatHistory.at(chatHistory.size() - 1);
		letterTextArea->setText(j["parts"][0]["text"].dump());
		letterTextArea->setText(letterTextArea->getText().substr(1, letterTextArea->getText().size() - 2)); // Remove quotation marks
	}
	letterTextArea->setReadOnly();
	letterTextArea->setSize(822, 995);
	letterTextArea->setTextSize(30);
	letterTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f + 26, (tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea)) / 2.0f - 8);
	letterTextArea->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::Transparent);
	letterTextArea->getRenderer()->setSelectedTextColor(tgui::Color::Black);
	letterTextArea->getRenderer()->setCaretColor(tgui::Color::Transparent);
	letterTextArea->getRenderer()->setTextColor(tgui::Color::Black);
	letterTextArea->getRenderer()->setFont(Macros::Fonts::Writing()); // new
	finishButton->setSize(240, 100);
	finishButton->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(finishButton), tgui::bindHeight(gui) - tgui::bindHeight(finishButton));

	finishButton->onClick([=] {
		Utils::Log::info("finishButton clicked");
		this->gameModel.getAudio().stopSfx("paper");
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});

	mainPanel->add(familyRelationshipPicture);
	mainPanel->add(mentalWellbeingPicture);
	mainPanel->add(letterTextArea);
	mainPanel->add(finishButton);

	this->gameModel.getAudio().playSfx("paper");
}