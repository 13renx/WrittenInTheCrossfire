#include "App.h"
#include "GameModel.h"
#include "ViewController.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

App::App() : gameModel(GameModel()), viewController(ViewController(gameModel)) {}

void App::run() {
	sf::RenderWindow& window = gameModel.getWindow();
	tgui::Gui& gui = gameModel.getGui();

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