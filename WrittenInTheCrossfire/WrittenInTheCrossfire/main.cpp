#include "App.h"
#include "Utils.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

int main() {
	bool isInitialized = false;
	std::unique_ptr<App> app;
	
	std::cout << "Initializing..." << std::endl;
	try {
		Utils::Log::init();
		tgui::Theme::setDefault("./Theme.txt");
		app = std::make_unique<App>();
		isInitialized = true;
	} catch(const std::exception& ex) {
		std::cerr << "Initialization failed\n";
		std::cerr << "Exception: " << std::string(ex.what()) << "\n";
	} catch(...) {
		std::cerr << "Initialization failed\n";
		std::cerr << "Unknown exception occurred\n";
	}

	if(!isInitialized) {
		system("pause");
		return -1;
	} else {
		Utils::Log::info("Initialization finished");
	}

	Utils::Log::info("Running app...");
	try {
		app->run();
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