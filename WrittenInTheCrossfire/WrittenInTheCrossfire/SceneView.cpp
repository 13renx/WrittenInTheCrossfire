#include "SceneView.h"
#include "SceneModel.h"
#include "GameModel.h"
#include "GameStateModel.h"
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

SceneView::SceneView(ViewController* viewController, GameModel& gameModel, SceneModel& sceneModel) : View(viewController, gameModel, tgui::Texture::Texture("")), sceneModel(sceneModel), gameStateModel(this->gameModel.getGameStateModel()), assets(this->sceneModel.getCheckpointAssets(this->gameStateModel.getCheckpoint())) {
	sf::RenderWindow& window = this->gameModel.getWindow();
	tgui::Gui& gui = this->gameModel.getGui();
	GameStateModel& gameStateModel = this->gameModel.getGameStateModel();
	gameStateModel.save();
	assetIndex = 1;

	if(gameStateModel.getCheckpoint() == 0 || gameStateModel.getCheckpoint() == 22) {
		
	} else {

	}

	// Initialize widgets
	scenePanel = tgui::Panel::create();
	dialogTextArea = tgui::TextArea::create();

	{
		tgui::Texture texture(std::get<1>(this->assets.at(0)));
		std::string text = std::get<2>(this->assets.at(0));
		scenePanel->getRenderer()->setTextureBackground(texture);
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

	scenePanel->onClick([=] {
		if(assetIndex < assets.size()) {
			tgui::Texture texture(std::get<1>(this->assets.at(assetIndex)));
			std::string text = std::get<2>(this->assets.at(assetIndex));
			scenePanel->getRenderer()->setTextureBackground(texture);
			dialogTextArea->setText(text);
			assetIndex++;
		} else {
			this->viewController->changeView(ViewController::ViewType::CAMP_VIEW);
		}
	});

	scenePanel->add(dialogTextArea);
	mainPanel->add(scenePanel);
}