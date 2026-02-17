#pragma once

#include "Client.h"
#include "GameModel.h"
#include "StoryModel.h"
#include "Structs.h"
#include "View.h"
#include "ViewController.h"
#include <atomic>
#include <memory>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class CampView : public View
{
	private:
		Client& client;
		GameState& gameState;
		StoryModel& storyModel;

		tgui::HorizontalLayout::Ptr buttonLayoutOne;
		tgui::Button::Ptr writeButton;
		tgui::Button::Ptr dontWriteButton;
		tgui::Button::Ptr exitTentButton;
		tgui::Picture::Ptr patriotismPicture;
		tgui::Group::Ptr interactableGroup;
		tgui::Group::Ptr familyRelationshipGroup;
		tgui::Panel::Ptr familyRelationshipPanel;
		tgui::Picture::Ptr familyRelationshipPicture;
		tgui::Group::Ptr newspaperGroup;
		tgui::TextArea::Ptr newspaperTextArea;
		tgui::Picture::Ptr newspaperPicture;
		tgui::Panel::Ptr newspaperPanel;
		tgui::Group::Ptr handMirrorGroup;
		tgui::Panel::Ptr handMirrorPanel;
		tgui::Picture::Ptr handMirrorPicture;
		tgui::Picture::Ptr mentalWellbeingPicture;
		//tgui::VerticalLayout::Ptr buttonLayoutTwo;
		//tgui::Button::Ptr cancelButton;
		//tgui::Button::Ptr selectButton;

		std::atomic<bool> isDontWriteClicked;
		bool isRunning;
		bool isPicFrameFar;
		bool isNewspaperFar;
		bool isHandMirrorFar;

	public:
		CampView(ViewController* viewController, GameModel& gameModel, StoryModel& storyModel);
		~CampView();

		void dontWrite();
}; 