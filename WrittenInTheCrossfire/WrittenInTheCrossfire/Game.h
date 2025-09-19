#pragma once

#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Game {
	private:
		sf::RenderWindow window;
		tgui::Gui gui;
		ViewManager viewManager;

	public:
		Game();
		void run();
};