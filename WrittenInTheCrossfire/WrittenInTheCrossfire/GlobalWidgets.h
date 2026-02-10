#pragma once

#include "Widgets.h"
#include <string>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class ViewController;

class GlobalWidgets
{
	private:
		tgui::Group::Ptr pauseGroup;
		tgui::Panel::Ptr pauseParentPanel;
		tgui::Panel::Ptr pauseChildPanel;
		tgui::GrowVerticalLayout::Ptr pauseLayout;
		tgui::Label::Ptr pauseGamePausedLabel;
		tgui::Label::Ptr pauseResumeLabel;
		tgui::Label::Ptr pauseExitLabel;
		tgui::ChildWindow::Ptr alertChildWindow;
		tgui::Label::Ptr alertLabel;
		tgui::Panel::Ptr mainPanel;
		
	public:
		GlobalWidgets(sf::RenderWindow& window, tgui::Gui& gui, ViewController* viewController);

		tgui::Group::Ptr getPauseGroup();
		tgui::ChildWindow::Ptr getAlertChildWindow();
		tgui::Label::Ptr getAlertLabel();
		tgui::Panel::Ptr getMainPanel();
};