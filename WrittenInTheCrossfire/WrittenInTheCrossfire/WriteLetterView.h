#pragma once

#include "Client.h"
#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <atomic>
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class WriteLetterView : public View
{
	private:
		Client& client;
		GameState& gameState;

		tgui::Panel::Ptr dialogPanel;
		tgui::TextArea::Ptr dialogTextArea;
		tgui::Label::Ptr dearLabel;
		tgui::TextArea::Ptr letterTextArea;
		tgui::VerticalLayout::Ptr buttonLayout;
		tgui::Group::Ptr familyRelationshipGroup;
		tgui::Panel::Ptr familyRelationshipPanel;
		tgui::Picture::Ptr familyRelationshipPicture;
		tgui::Picture::Ptr mentalWellbeingPicture;
		tgui::Button::Ptr cancelButton;
		tgui::Button::Ptr sendButton;

		std::atomic<bool> isSendClicked;
		bool isRunning;
		bool isPicFrameFar;

	public:
		WriteLetterView(ViewController* viewController, GameModel& gameModel);
		~WriteLetterView();

		void send();
};