#pragma once

#include "Client.h"
#include "GameModel.h"
#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class CampView : public View
{
	private:
		Client& client;
		GameModel gameModel;
		
		tgui::HorizontalLayout::Ptr buttonLayoutOne;
		tgui::Button::Ptr writeButton;
		tgui::Button::Ptr dontWriteButton;
		
		tgui::VerticalLayout::Ptr buttonLayoutTwo;
		tgui::Button::Ptr cancelButton;
		tgui::Button::Ptr selectButton;

	public:
		CampView(Client& client, tgui::Gui& gui, ViewManager* viewManager);
}; 