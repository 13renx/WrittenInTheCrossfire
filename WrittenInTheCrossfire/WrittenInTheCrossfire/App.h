#pragma once

#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class App {
	private:
		sf::RenderWindow window;
		tgui::Gui gui;
		ViewManager viewManager;

	public:
		App();
		void run();
};