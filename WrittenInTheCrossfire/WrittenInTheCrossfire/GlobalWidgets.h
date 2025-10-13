#pragma once

#include "Widgets.h"
#include <string>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class ViewController;

class GlobalWidgets
{
	private:
		tgui::Panel::Ptr menuParentPanel;
		tgui::Panel::Ptr menuChildPanel;
		tgui::GrowVerticalLayout::Ptr menuLayout;
		tgui::Label::Ptr menuResumeLabel;
		tgui::Label::Ptr menuExitLabel;
		tgui::ChildWindow::Ptr alertChildWindow;
		tgui::Label::Ptr alertLabel;
		tgui::Panel::Ptr mainPanel;
		
	public:
		GlobalWidgets(sf::RenderWindow& window, tgui::Gui& gui, ViewController* viewController);

		tgui::Panel::Ptr getMenuParentPanel();
		tgui::ChildWindow::Ptr getAlertChildWindow();
		tgui::Label::Ptr getAlertLabel();
		tgui::Panel::Ptr getMainPanel();
};