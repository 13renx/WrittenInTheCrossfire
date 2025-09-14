#include "Game.h"

Game::Game() 

void Game::run() {
	while(window.isOpen()) {
		processEvents();
		update();
		render();
	}
}