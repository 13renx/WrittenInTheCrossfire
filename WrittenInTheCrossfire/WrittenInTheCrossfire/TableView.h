#pragma once

#include "Client.h"
#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class TableView : public View
{
	private:
		Client& client;
		GameStateModel& gameStateModel;

		tgui::Panel::Ptr dialogPanel;
		tgui::TextArea::Ptr dialogTextArea;
		tgui::Label::Ptr dearLabel;
		tgui::TextArea::Ptr letterTextArea;
		tgui::VerticalLayout::Ptr buttonLayout;
		tgui::Button::Ptr cancelButton;
		tgui::Button::Ptr sendButton;
		bool isSendRunning;
		bool isSendClicked;

	public:
		TableView(ViewController* viewController, GameModel& gameModel);

		void send();
};