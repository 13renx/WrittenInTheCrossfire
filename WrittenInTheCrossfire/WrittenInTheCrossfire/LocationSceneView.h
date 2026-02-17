#pragma once

#include "StoryModel.h"
#include "Structs.h"
#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class LocationSceneView : public View
{
private:
	StoryModel& storyModel;
	GameState& gameState;
	std::vector<LocationSceneAsset> locationSceneAssets;
	size_t assetIndex;

	tgui::Panel::Ptr backgroundPanel;
	tgui::Panel::Ptr foregroundPanel;
	tgui::TextArea::Ptr dialogueTextArea;

public:
	LocationSceneView(ViewController* viewController, GameModel& gameModel, StoryModel& storyModel);
};