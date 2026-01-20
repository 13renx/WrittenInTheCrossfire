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
		tgui::Button::Ptr exitTentButton;
		tgui::Picture::Ptr patriotismPicture;
		tgui::Group::Ptr objectsGroup;
		tgui::Group::Ptr familyRelationshipGroup;
		tgui::Panel::Ptr familyRelationshipPanel;
		tgui::Picture::Ptr familyRelationshipPicture;
		tgui::Group::Ptr newspaperGroup;
		tgui::Panel::Ptr newspaperPanel;
		tgui::Picture::Ptr newspaperPicture;
		tgui::Group::Ptr handMirrorGroup;
		tgui::Panel::Ptr handMirrorPanel;
		tgui::Picture::Ptr handMirrorPicture;
		tgui::Picture::Ptr mentalWellbeingPicture;
		//tgui::VerticalLayout::Ptr buttonLayoutTwo;
		//tgui::Button::Ptr cancelButton;
		//tgui::Button::Ptr selectButton;

		bool isRunning;
		bool isPicFrameFar;
		bool isNewspaperFar;
		bool isHandMirrorFar;
		bool isDontWriteClicked;

	public:
		CampView(ViewController* viewController, GameModel& gameModel);
		~CampView();

		void dontWrite();
}; 