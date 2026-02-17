#include "LocationSceneView.h"
#include "StoryModel.h"
#include "GameModel.h"
#include "GameState.h"
#include "Macros.h"
#include "Utils.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <filesystem>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

LocationSceneView::LocationSceneView(ViewController* viewController, GameModel& gameModel, StoryModel& storyModel) : View(viewController, gameModel, tgui::Texture::Texture("")), storyModel(storyModel), gameState(this->gameModel.getGameState()), locationSceneAssets(this->storyModel.getMainSceneAssets(this->gameState.getCheckpoint())) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	this->gameModel.getAudio().stopMusic();
	GameState& gameState = this->gameModel.getGameState();
	gameState.save();
	assetIndex = 0;

	// Initialize widgets
	backgroundPanel = tgui::Panel::create();
	foregroundPanel = tgui::Panel::create();
	dialogueTextArea = tgui::TextArea::create();

	backgroundPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
	dialogueTextArea->setText("...");
	dialogueTextArea->setReadOnly();
	dialogueTextArea->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::Transparent);
	dialogueTextArea->getRenderer()->setCaretColor(tgui::Color::Transparent);
	dialogueTextArea->setSize(1200, 300);
	dialogueTextArea->setTextSize(34);
	dialogueTextArea->getRenderer()->setTextColor(tgui::Color::White);
	dialogueTextArea->getRenderer()->setBackgroundColor(tgui::Color(128, 128, 128, 60));
	dialogueTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(dialogueTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(dialogueTextArea) - 50);
	{
		if(locationSceneAssets.at(0).backgroundTexture != "") {
			tgui::Texture texture(locationSceneAssets.at(0).backgroundTexture);
			scenePanel->getRenderer()->setTextureBackground(texture);
		}
	}
	dialogueTextArea->getRenderer()->setPadding(20);

	scenePanel->onClick([=, &gameState] {
		Utils::Log::debugInfo("scenePanel clicked");
		int checkpoint = gameState.getCheckpoint();

		if(checkpoint == 0 && assetIndex == locationSceneAssets.size()) { // Prelude
			gameState.incrementCheckpoint();
			this->viewController->changeView(ViewController::ViewType::MAIN_SCENE_VIEW);
		}
		else if(checkpoint == 1 && assetIndex == locationSceneAssets.size()) { // After Prelude
			this->viewController->changeView(ViewController::ViewType::CAMP_VIEW); // Skip ReadLetterView
		}
		else if((checkpoint == 19 || checkpoint < 0) && assetIndex == locationSceneAssets.size()) { // Regular/Bad ending
			std::filesystem::remove("game.json");
			Utils::Log::debugInfo("game.json deleted");
			this->viewController->changeView(ViewController::ViewType::MAIN_MENU_VIEW);
		}
		else if(assetIndex < locationSceneAssets.size()) {
			if(locationSceneAssets.at(assetIndex).backgroundTexture != "") {
				tgui::Texture texture(locationSceneAssets.at(assetIndex).backgroundTexture);
				scenePanel->getRenderer()->setTextureBackground(texture);
			}
			else {
				scenePanel->getRenderer()->setTextureBackground("");
			}
			std::string text = locationSceneAssets.at(assetIndex).dialogue;
			dialogueTextArea->setText(text);
			assetIndex++;
		}
		else {
			this->viewController->changeView(ViewController::ViewType::READ_LETTER_VIEW); // View Mom's letter
		}
		});
	scenePanel->add(dialogueTextArea);
	mainPanel->add(scenePanel);
}