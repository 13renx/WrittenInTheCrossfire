#include "Game.h"

Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Written In The Crossfire", sf::State::Fullscreen) {}

void Game::run() {
	while(window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {
	while(const auto event = window.pollEvent()) {
		if(event->is<sf::Event::Closed>()) {
			window.close();
		}
	}
}

void Game::update() {}

void Game::render() {
	window.clear();

	window.display();
}