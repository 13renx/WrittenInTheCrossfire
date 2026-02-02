#include "App.h"
#include "Utils.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

int main() {
	Utils::Log::init();
	tgui::Theme::setDefault("Theme.txt");

	App app = App();
	app.run();

	return 0;
}