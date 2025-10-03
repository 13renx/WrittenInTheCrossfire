#include "GameModel.h"
#include "Client.h"
#include "GameStateModel.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

GameModel::GameModel() : window(sf::VideoMode({ 1920, 1080 }), "Written In The Crossfire", sf::State::Fullscreen), gui(window), client(Client()), gameStateModel(GameStateModel()) {
	window.setFramerateLimit(60);
}

sf::RenderWindow& GameModel::getWindow() {
	return window;
}

tgui::Gui& GameModel::getGui() {
	return gui;
}

Client& GameModel::getClient() {
	return client;
}

GameStateModel& GameModel::getGameStateModel() {
	return gameStateModel;
}