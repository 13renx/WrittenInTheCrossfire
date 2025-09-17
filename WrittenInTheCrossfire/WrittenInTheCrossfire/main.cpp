#include "Game.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

int main() {
	tgui::Theme::setDefault("Assets/Themes/MainTheme.txt");

	Game game = Game();
	game.run();

	return 0;
}