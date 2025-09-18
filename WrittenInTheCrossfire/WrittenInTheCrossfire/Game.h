#pragma once

#include "View.h"
#include <memory>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Game {
	private:
		sf::RenderWindow window;
		tgui::Gui gui;
		std::shared_ptr<View> activeView;

	public:
		Game();
		void run();
};