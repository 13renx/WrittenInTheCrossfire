#include "MainSceneView.h"
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

MainSceneView::MainSceneView(ViewController* viewController, GameModel& gameModel, StoryModel& storyModel) : View(viewController, gameModel, tgui::Texture::Texture("")), storyModel(storyModel), gameState(this->gameModel.getGameState()), mainSceneAssets(this->storyModel.getMainSceneAssets(this->gameState.getCheckpoint())) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	this->gameModel.getAudio().stopMusic();
	GameState& gameState = this->gameModel.getGameState();
	gameState.save();
	assetIndex = 0;

	// Initialize widgets
	scenePanel = tgui::Panel::create();
	dialogTextArea = tgui::TextArea::create();
	
	scenePanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
	dialogTextArea->setText("...");
	dialogTextArea->setReadOnly();
	dialogTextArea->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::Transparent);
	dialogTextArea->getRenderer()->setCaretColor(tgui::Color::Transparent);
	dialogTextArea->setSize(1200, 300);
	dialogTextArea->setTextSize(34);
	dialogTextArea->getRenderer()->setTextColor(tgui::Color::White);
	dialogTextArea->getRenderer()->setBackgroundColor(tgui::Color(128, 128, 128, 60));
	dialogTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(dialogTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(dialogTextArea) - 50);
	{
		if(mainSceneAssets.at(0).backgroundTexture != "") {
			tgui::Texture texture(mainSceneAssets.at(0).backgroundTexture);
			scenePanel->getRenderer()->setTextureBackground(texture);
		}
	}
	dialogTextArea->getRenderer()->setPadding(20);
	
	scenePanel->onClick([=, &gameState] {
		Utils::Log::debugInfo("scenePanel clicked");
		int checkpoint = gameState.getCheckpoint();

		if(checkpoint == 0 && assetIndex == mainSceneAssets.size()) { // Prelude
			gameState.incrementCheckpoint();
			this->viewController->changeView(ViewController::ViewType::MAIN_SCENE_VIEW);
		} else if(checkpoint == 1 && assetIndex == mainSceneAssets.size()) { // After Prelude
			this->viewController->changeView(ViewController::ViewType::CAMP_VIEW); // Skip ReadLetterView
		} else if((checkpoint == 19 || checkpoint < 0) && assetIndex == mainSceneAssets.size()) { // Regular/Bad ending
			std::filesystem::remove("game.json");
			Utils::Log::debugInfo("game.json deleted");
			this->viewController->changeView(ViewController::ViewType::MAIN_MENU_VIEW);
		} else if(assetIndex < mainSceneAssets.size()) {
			if(mainSceneAssets.at(assetIndex).backgroundTexture != "") {
				tgui::Texture texture(mainSceneAssets.at(assetIndex).backgroundTexture);
				scenePanel->getRenderer()->setTextureBackground(texture);
			} else {
				scenePanel->getRenderer()->setTextureBackground("");
			}
			std::string text = mainSceneAssets.at(assetIndex).dialogue;
			dialogTextArea->setText(text);
			assetIndex++;
		} else {
			this->viewController->changeView(ViewController::ViewType::READ_LETTER_VIEW); // View Mom's letter
		}
	});
	scenePanel->add(dialogTextArea);
	mainPanel->add(scenePanel);
}