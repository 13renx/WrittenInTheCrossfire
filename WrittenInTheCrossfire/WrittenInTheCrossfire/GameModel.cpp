#include "Audio.h"
#include "Fonts.h"
#include "GameModel.h"
#include "Client.h"
#include "GameState.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

GameModel::GameModel() : window(sf::VideoMode({ 1920, 1080 }), "Written In The Crossfire", sf::State::Fullscreen), 
	gui(window),
	fonts(),
	audio(), 
	client(), 
	gameState() {
		window.setFramerateLimit(60);
}

sf::RenderWindow& GameModel::getWindow() {
	return window;
}

tgui::Gui& GameModel::getGui() {
	return gui;
}

Fonts& GameModel::getFonts() {
	return fonts;
}

Audio& GameModel::getAudio() {
	return audio;
}

Client& GameModel::getClient() {
	return client;
}

GameState& GameModel::getGameState() {
	return gameState;
}