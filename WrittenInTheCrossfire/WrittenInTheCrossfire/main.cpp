#include "App.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

int main() {
	tgui::Theme::setDefault("Theme.txt");

	App app = App();
	app.run();

	return 0;
}