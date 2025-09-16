#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Script
{
	protected:
		tgui::Gui& gui;

	public:
		Script(tgui::Gui& g);
};