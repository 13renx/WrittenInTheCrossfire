#pragma once

#include "Audio.h"
#include "Client.h"
#include "Fonts.h"
#include "GameState.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class GameModel {
	private:
		sf::RenderWindow window;
		tgui::Gui gui;
		Fonts fonts;
		Audio audio;
		Client client;
		GameState gameState;

	public:
		GameModel();

		sf::RenderWindow& getWindow();
		tgui::Gui& getGui();
		Fonts& getFonts();
		Audio& getAudio();
		Client& getClient();
		GameState& getGameState();
};