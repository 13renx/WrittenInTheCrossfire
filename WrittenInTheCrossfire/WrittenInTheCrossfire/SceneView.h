#pragma once

#include "Client.h"
#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class SceneView : public View
{
	private:
		Client& client;
		std::unique_ptr<GameModel> gameModel;

	public:
		SceneView(Client& client, tgui::Gui& gui, ViewController* viewManager);
};