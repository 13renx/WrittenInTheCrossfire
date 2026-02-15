#include "App.h"
#include "Utils.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

int main() {
	Utils::Log::init();
	tgui::Theme::setDefault("Theme.txt");

	App app = App();
	try {
		app.run();
	} catch(const std::exception& ex) {
		Utils::Log::critical("Exception: " + std::string(ex.what()));
	} catch(...) {
		Utils::Log::critical("Unknown exception occurred");
	}
	
	return 0;
}