#pragma once

#include "Manager.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Game {
	private:
		sf::RenderWindow window;
		tgui::Gui gui;
		Manager activeManager;

	public:
		Game();
		void run(); // Game loop
};