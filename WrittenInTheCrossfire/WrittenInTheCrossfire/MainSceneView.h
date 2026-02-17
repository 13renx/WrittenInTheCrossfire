#pragma once

#include "StoryModel.h"
#include "Structs.h"
#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MainSceneView : public View
{
	private:
		StoryModel& storyModel;
		GameState& gameState;
		std::vector<MainSceneAsset> mainSceneAssets;
		size_t assetIndex;

		tgui::Panel::Ptr scenePanel;
		tgui::TextArea::Ptr dialogueTextArea;

	public:
		MainSceneView(ViewController* viewController, GameModel& gameModel, StoryModel& storyModel);
};