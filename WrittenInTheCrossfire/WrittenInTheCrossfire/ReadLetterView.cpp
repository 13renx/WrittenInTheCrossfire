#include "ReadLetterView.h"
#include "Fonts.h"
#include "GameModel.h"
#include "Macros.h"
#include "Utils.h"
#include "View.h"
#include "ViewController.h"
#include <nlohmann/json.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

using json = nlohmann::json;

ReadLetterView::ReadLetterView(ViewController* viewController, GameModel& gameModel) : View(viewController, gameModel, "./Assets/Textures/Backgrounds/ReadLetterView.PNG"), gameState(this->gameModel.getGameState()) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	Fonts& fonts = this->gameModel.getFonts();
	Stats& stats = gameState.getCurrentStats();
	isPicFrameFar = true;

	// Initialize widgets
	letterTextArea = tgui::TextArea::create();
	finishButton = tgui::Button::create("FINISH READING");
	familyRelationshipGroup = tgui::Group::create();
	familyRelationshipPicture = Widgets::Pictures::createPictureButton(window);
	familyRelationshipPanel = tgui::Panel::create();
	mentalWellbeingPicture = tgui::Picture::create();

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
	{
		std::vector<json> chatHistory = gameState.getChatHistory();
		json j = chatHistory.at(chatHistory.size() - 1);
		letterTextArea->setText(j["parts"][0]["text"].dump());
		letterTextArea->setText(letterTextArea->getText().substr(1, letterTextArea->getText().size() - 2)); // Remove quotation marks
	}
	familyRelationshipPanel->setVisible(false);
	letterTextArea->setReadOnly();
	letterTextArea->setSize(822, 995);
	letterTextArea->setTextSize(30);
	letterTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(letterTextArea)) / 2.0f + 26, (tgui::bindHeight(gui) - tgui::bindHeight(letterTextArea)) / 2.0f - 8);
	letterTextArea->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::Transparent);
	letterTextArea->getRenderer()->setSelectedTextColor(tgui::Color::Black);
	letterTextArea->getRenderer()->setCaretColor(tgui::Color::Transparent);
	letterTextArea->getRenderer()->setTextColor(tgui::Color::Black);
	letterTextArea->getRenderer()->setFont(fonts.getWriting());
	letterTextArea->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	finishButton->setSize(240, 100);
	finishButton->setPosition(tgui::bindWidth(gui) - tgui::bindWidth(finishButton), tgui::bindHeight(gui) - tgui::bindHeight(finishButton));

	familyRelationshipPanel->onClick([=, &gui, &stats] {
		Utils::Log::debugInfo("familyRelationshipPanel clicked");

		if(!this->isPicFrameFar) {
			familyRelationshipGroup->moveToBack();
			familyRelationshipPanel->setVisible(false);
			finishButton->setVisible(true);
			familyRelationshipPicture->setSize(560, 516);
			familyRelationshipPicture->setPosition(0, 0);

			if(stats.familyRelationship > 75) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Very Good.png");
			} else if(stats.familyRelationship > 50) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Good.png");
			} else if(stats.familyRelationship > 25) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Bad.png");
			} else if(stats.familyRelationship < 26) {
				familyRelationshipPicture->getRenderer()->setTexture("./Assets/Textures/Interactables/Family Relationship/Far/Worse.png");
			}

			this->isPicFrameFar = true;
		}
		});
	familyRelationshipPicture->onClick([=, &gui, &stats] {
		Utils::Log::debugInfo("familyRelationshipPicture clicked");

		if(this->isPicFrameFar) {
			familyRelationshipGroup->moveToFront();
			familyRelationshipPanel->setVisible(true);
			finishButton->setVisible(false);
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

			this->isPicFrameFar = false;
		} else {
			familyRelationshipGroup->moveToBack();
			familyRelationshipPanel->setVisible(false);
			finishButton->setVisible(true);
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

			familyRelationshipPicture->setPosition(0, 0);
			this->isPicFrameFar = true;
		}
	});
	finishButton->onClick([=] {
		Utils::Log::debugInfo("finishButton clicked");
		this->gameModel.getAudio().stopSfx("letter");
		this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
	});

	mainPanel->add(familyRelationshipGroup);
	mainPanel->add(mentalWellbeingPicture);
	mainPanel->add(letterTextArea);
	mainPanel->add(finishButton);
	familyRelationshipGroup->add(familyRelationshipPanel);
	familyRelationshipGroup->add(familyRelationshipPicture);

	this->gameModel.getAudio().playSfx("letter");
}