#pragma once

#include "GameModel.h"
#include "Widgets.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class ViewController;

class View
{
	protected:
		ViewController* viewController;
		GameModel& gameModel;
		tgui::Panel::Ptr mainPanel;
		tgui::ChildWindow::Ptr alertChildWindow;
		tgui::Label::Ptr alertLabel;

	public:
		View(ViewController* viewController, GameModel& gameModel, tgui::Texture mainPanelTexture);
};