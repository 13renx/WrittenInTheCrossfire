#pragma once

#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MapView : public View
{
	private:
		tgui::Picture::Ptr bunkerPicture;
		tgui::Picture::Ptr mealAreaPicture;
		tgui::Picture::Ptr storageBunkerPicture;
		tgui::Button::Ptr backButton;

	public:
		MapView(ViewController* viewController, GameModel& gameModel);
};