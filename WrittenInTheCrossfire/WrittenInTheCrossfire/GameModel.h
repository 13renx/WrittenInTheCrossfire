#pragma once

#include "Audio.h"
#include "Client.h"
#include "GameStateModel.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class GameModel {
	private:
		sf::RenderWindow window;
		tgui::Gui gui;
		Audio audio;
		Client client;
		GameStateModel gameStateModel;

	public:
		GameModel();

		sf::RenderWindow& getWindow();
		tgui::Gui& getGui();
		Audio& getAudio();
		Client& getClient();
		GameStateModel& getGameStateModel();
};