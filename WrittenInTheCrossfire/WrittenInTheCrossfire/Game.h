#pragma once

#include <SFML/Graphics.hpp>

class Game {
	sf::RenderWindow window;

	public:
		Game();
		void run();

	private:
		void processEvents();
		void update();
		void render();
};