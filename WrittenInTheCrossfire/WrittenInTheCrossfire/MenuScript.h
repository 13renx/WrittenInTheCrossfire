#pragma once

#include "Script.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MenuScript : public Script
{
	private:
		tgui::Label::Ptr exitLabel;
		tgui::Panel::Ptr exitPanel;
		tgui::Group::Ptr exitGroup;

	public:
		MenuScript(tgui::Gui& g);
};