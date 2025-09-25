#pragma once

#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class ViewManager;

class View
{
	protected:
		tgui::Gui& gui;
		tgui::Panel::Ptr mainPanel;
		ViewManager* viewManager;
		tgui::ChildWindow::Ptr alertChildWindow;
		tgui::Label::Ptr alertLabel;

	public:
		View(tgui::Gui& gui, ViewManager* viewManager, tgui::Texture mainPanelTexture);
};