#include "Game.h"
#include "MenuView.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Written In The Crossfire", sf::State::Fullscreen), gui(window), activeView(std::make_shared<MenuView>(gui, activeView)) {
	window.setFramerateLimit(60);
}

void Game::run() {
	while(window.isOpen()) {
		while(const std::optional event = window.pollEvent()) {
			if(event->is<sf::Event::Closed>()) {
				window.close();
			}

			gui.handleEvent(*event);
		}

		window.clear();
		gui.draw();
		window.display();
	}
}