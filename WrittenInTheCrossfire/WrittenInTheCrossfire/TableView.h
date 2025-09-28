#pragma once

#include "Client.h"
#include "GameModel.h"
#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class TableView : public View
{
	private:
		Client& client;
		GameModel gameModel;

		tgui::Label::Ptr dearLabel;
		tgui::TextArea::Ptr letterTextArea;
		tgui::VerticalLayout::Ptr buttonLayout;
		tgui::Button::Ptr cancelButton;
		tgui::Button::Ptr sendButton;

	public:
		TableView(Client& client, tgui::Gui& gui, ViewManager* viewManager);
};