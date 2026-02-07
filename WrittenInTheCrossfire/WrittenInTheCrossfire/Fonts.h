#pragma once

#include <TGUI/TGUI.hpp>

class Fonts
{
	private:
		tgui::Font title;
		tgui::Font writing;
	
	public:
		Fonts();

		tgui::Font& getTitle();
		tgui::Font& getWriting();
};