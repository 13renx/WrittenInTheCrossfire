#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Screen
{
	protected:
		tgui::Panel::Ptr panel;

	public:
		Screen();

		tgui::Panel::Ptr getPanel();
};