#include "App.h"
#include "GameModel.h"
#include "GlobalWidgets.h"
#include "Utils.h"
#include "ViewController.h"
#include <memory>
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

App::App() : gameModel(GameModel()), viewController(ViewController(gameModel)) {}

void App::run() {
	sf::RenderWindow& window = gameModel.getWindow();
	tgui::Gui& gui = gameModel.getGui();
	tgui::Group::Ptr pauseGroup = viewController.getGlobalWidgets()->getPauseGroup();
	ViewController::ViewType& activeViewType = viewController.getActiveViewType();

	while(window.isOpen()) {
		while(const std::optional event = window.pollEvent()) {
			if(event->is<sf::Event::Closed>()) {
				Utils::Log::info("Window closed");
				window.close();
			}

			if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if(keyPressed->scancode == sf::Keyboard::Scan::Escape) {
					Utils::Log::info("Esc key pressed");

					if(activeViewType == ViewController::ViewType::SCENE_VIEW || activeViewType == ViewController::ViewType::READ_LETTER_VIEW) {
						if(pauseGroup->isVisible()) {
							pauseGroup->setVisible(false);
						} else {
							pauseGroup->setVisible(true);
						}
					}
				}
			}

			gui.handleEvent(*event);
		}

		window.clear();
		gui.draw();
		window.display();
	}
}