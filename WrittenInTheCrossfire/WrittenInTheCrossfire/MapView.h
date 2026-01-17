#pragma once

#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MapView : public View
{
	private:
		tgui::Button::Ptr backButton;

	public:
		MapView(ViewController* viewController, GameModel& gameModel);
};