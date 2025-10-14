#pragma once

#include "SceneModel.h"
#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <string>
#include <tuple>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class SceneView : public View
{
	private:
		SceneModel sceneModel;
		GameStateModel& gameStateModel;
		//std::vector<std::tuple<int, std::string, std::string>>& assets;
		size_t assetIndex;

		tgui::TextArea::Ptr dialogTextArea;

	public:
		SceneView(ViewController* viewController, GameModel& gameModel);
};