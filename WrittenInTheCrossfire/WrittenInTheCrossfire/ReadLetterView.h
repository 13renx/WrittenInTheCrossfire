#pragma once

#include "GameModel.h"
#include "GameState.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class ReadLetterView : public View
{
	private:
		GameState& gameState;

		tgui::TextArea::Ptr letterTextArea;
		tgui::Button::Ptr finishButton;
		tgui::Picture::Ptr familyRelationshipPicture;
		tgui::Picture::Ptr mentalWellbeingPicture;

	public:
		ReadLetterView(ViewController* viewController, GameModel& gameModel);
};