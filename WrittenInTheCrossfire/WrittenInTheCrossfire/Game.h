#pragma once

#include "Screen.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Game {
	sf::RenderWindow window;
	tgui::Gui gui;
	Screen activeScreen;

	public:
		Game();
		void run(); // Game loop
};