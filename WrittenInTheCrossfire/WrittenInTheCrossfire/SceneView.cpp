#include "SceneView.h"
#include "SceneModel.h"
#include "GameModel.h"
#include "GameState.h"
#include "Macros.h"
#include "View.h"
#include "ViewController.h"
#include "Widgets.h"
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

SceneView::SceneView(ViewController* viewController, GameModel& gameModel, SceneModel& sceneModel) : View(viewController, gameModel, tgui::Texture::Texture("")), sceneModel(sceneModel), gameState(this->gameModel.getGameState()), assets(this->sceneModel.getCheckpointAssets(this->gameState.getCheckpoint())) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	this->gameModel.getAudio().stopMusic();
	GameState& gameState = this->gameModel.getGameState();
	gameState.save();
	assetIndex = 1;

	// Initialize widgets
	scenePanel = tgui::Panel::create();
	dialogTextArea = tgui::TextArea::create();

	scenePanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
	{
		if(std::get<1>(this->assets.at(0)) != "") {
			tgui::Texture texture(std::get<1>(this->assets.at(0)));
			scenePanel->getRenderer()->setTextureBackground(texture);
		}
		std::string text = std::get<2>(this->assets.at(0));
		dialogTextArea->setText(text);
	}
	dialogTextArea->setReadOnly();
	dialogTextArea->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::Transparent);
	dialogTextArea->getRenderer()->setSelectedTextColor(Macros::Colors::Redwood);
	dialogTextArea->getRenderer()->setCaretColor(tgui::Color::Transparent);
	dialogTextArea->setSize(1200, 300);
	dialogTextArea->setTextSize(30);
	dialogTextArea->getRenderer()->setBackgroundColor(Macros::Colors::TransparentGrey);
	dialogTextArea->setPosition((tgui::bindWidth(gui) - tgui::bindWidth(dialogTextArea)) / 2.0f, tgui::bindHeight(gui) - tgui::bindHeight(dialogTextArea) - 50);

	scenePanel->onClick([=, &gameState] {
		int checkpoint = gameState.getCheckpoint();

		if(checkpoint == 0 && assetIndex == assets.size()) {
			this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
		} else if(checkpoint == 22 && assetIndex == assets.size()) {
			this->viewController->changeView(ViewController::ViewType::MAIN_MENU_VIEW);
		} else if(assetIndex < assets.size()) {
			if(std::get<1>(this->assets.at(assetIndex)) != "") {
				tgui::Texture texture(std::get<1>(this->assets.at(assetIndex)));
				scenePanel->getRenderer()->setTextureBackground(texture);
			} else {
				scenePanel->getRenderer()->setTextureBackground("");
			}
			std::string text = std::get<2>(this->assets.at(assetIndex));
			dialogTextArea->setText(text);
			assetIndex++;
		} else {
			this->viewController->changeView(ViewController::ViewType::READ_LETTER_VIEW);
		}
	});

	scenePanel->add(dialogTextArea);
	mainPanel->add(scenePanel);
}