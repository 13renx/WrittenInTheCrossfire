#include "App.h"
#include "GameModel.h"
#include "GlobalWidgets.h"
#include "ViewController.h"
#include <memory>
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

App::App() : gameModel(GameModel()), viewController(ViewController(gameModel)) {}

void App::run() {
	sf::RenderWindow& window = gameModel.getWindow();
	tgui::Gui& gui = gameModel.getGui();
	tgui::Panel::Ptr menuParentPanel = viewController.getGlobalWidgets()->getMenuParentPanel();
	ViewController::ViewType& activeViewType = viewController.getActiveViewType();

	while(window.isOpen()) {
		while(const std::optional event = window.pollEvent()) {
			if(event->is<sf::Event::Closed>()) {
				window.close();
			}

			if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if(keyPressed->scancode == sf::Keyboard::Scan::Escape && (activeViewType == ViewController::ViewType::SCENE_VIEW || activeViewType == ViewController::ViewType::CAMP_VIEW || activeViewType == ViewController::ViewType::TABLE_VIEW)) {
					if(menuParentPanel->isVisible()) {
						menuParentPanel->setVisible(false);
					} else {
						menuParentPanel->setVisible(true);
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