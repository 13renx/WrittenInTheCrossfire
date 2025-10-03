#pragma once

#include "Client.h"
#include "GameStateModel.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class GameModel {
	private:
		sf::RenderWindow window;
		tgui::Gui gui;
		Client client;
		GameStateModel gameStateModel;

	public:
		GameModel();

		sf::RenderWindow& getWindow();
		tgui::Gui& getGui();
		Client& getClient();
		GameStateModel& getGameStateModel();
};