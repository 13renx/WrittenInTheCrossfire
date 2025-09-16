#pragma once

#include "Screen.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Game {
	private:
		sf::RenderWindow window;
		tgui::Gui gui;
		Screen activeScreen;

	public:
		Game();
		void run(); // Game loop
};