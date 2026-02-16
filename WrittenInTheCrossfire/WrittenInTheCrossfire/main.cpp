#include "App.h"
#include "Utils.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

int main() {
	bool isInitialized = false;

	std::cout << "Initializing..." << std::endl;
	tgui::Theme::setDefault("./Theme.txt");
	try {
		Utils::Log::init();
		isInitialized = true;
	} catch(const std::exception& ex) {
		std::cerr << "Initialization failed\n";
		std::cerr << "Exception: " << std::string(ex.what()) << "\n";
		std::cerr << "TIP: Try running WrittenInTheCrossfire.exe as administrator\n";
	} catch(...) {
		std::cerr << "Initialization failed\n";
		std::cerr << "Unknown exception occurred\n";
	}

	if(!isInitialized) {
		system("pause");
		return -1;
	}

	App app = App();
	try {
		app.run();
		Utils::Log::info("App stopped running");
	} catch(const std::exception& ex) {
		Utils::Log::critical("App crashed");
		Utils::Log::critical(fmt::format("Exception: {}", ex.what()));
		system("pause");
		return -1;
	} catch(...) {
		Utils::Log::critical("App crashed");
		Utils::Log::critical("Unknown exception occurred");
		system("pause");
		return -1;
	}
	
	return 0;
}