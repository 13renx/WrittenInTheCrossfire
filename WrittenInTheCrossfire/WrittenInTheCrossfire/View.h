#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class View
{
	protected:
		tgui::Gui& gui;
		tgui::Panel::Ptr mainPanel;
		std::shared_ptr<View> activeView;

	public:
		View(tgui::Gui& g, std::shared_ptr<View> v);
};