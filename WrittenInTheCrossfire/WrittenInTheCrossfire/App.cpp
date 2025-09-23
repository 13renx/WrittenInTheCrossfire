#include "App.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

App::App() : window(sf::VideoMode({ 1920, 1080 }), "Written In The Crossfire", sf::State::Fullscreen), gui(window) , viewManager(gui) {
	window.setFramerateLimit(60);
}

void App::run() {
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