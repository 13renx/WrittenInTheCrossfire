#pragma once

#include "Widgets.h"
#include <string>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class GlobalWidgets
{
	private:
		tgui::ChildWindow::Ptr alertChildWindow;
		tgui::Label::Ptr alertLabel;
		tgui::Panel::Ptr mainPanel;
		
	public:
		GlobalWidgets(tgui::Gui& gui);

		tgui::Panel::Ptr getMainPanel();
		tgui::ChildWindow::Ptr getAlertChildWindow();
		tgui::Label::Ptr getAlertLabel();
};