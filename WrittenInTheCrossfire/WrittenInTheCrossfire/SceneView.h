#pragma once

#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class SceneView : public View
{
	private:
		GameStateModel& gameStateModel;

		tgui::TextArea::Ptr dialogTextArea;

	public:
		SceneView(ViewController* viewController, GameModel& gameModel);
};