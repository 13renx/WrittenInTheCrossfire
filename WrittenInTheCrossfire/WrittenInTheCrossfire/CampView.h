#pragma once

#include "Client.h"
#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class CampView : public View
{
	private:
		Client& client;
		GameState& gameState;

		tgui::HorizontalLayout::Ptr buttonLayoutOne;
		tgui::Button::Ptr writeButton;
		tgui::Button::Ptr dontWriteButton;
		tgui::Panel::Ptr patriotismPanel;
		tgui::Panel::Ptr familyRelationshipPanel;
		tgui::Panel::Ptr mentalWellbeingPanel;
		//tgui::VerticalLayout::Ptr buttonLayoutTwo;
		//tgui::Button::Ptr cancelButton;
		//tgui::Button::Ptr selectButton;

		bool isRunning;
		bool isDontWriteClicked;

	public:
		CampView(ViewController* viewController, GameModel& gameModel);
		~CampView();

		void dontWrite();
}; 