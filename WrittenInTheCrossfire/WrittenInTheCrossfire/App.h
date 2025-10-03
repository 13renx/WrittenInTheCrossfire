#pragma once

#include "GameModel.h"
#include "ViewController.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class App {
	GameModel gameModel;
	ViewController viewController;

	public:
		App();
		void run();
};