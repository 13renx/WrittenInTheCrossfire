#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Screen
{
	protected:
		tgui::Gui& gui;
		tgui::Panel::Ptr panel;

	public:
		Screen(tgui::Gui& g);
};