#pragma once

#include "Screen.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MenuScreen : public Screen
{
	protected:
		tgui::Label::Ptr titleLabel;
		tgui::Label::Ptr newGameLabel;
		tgui::Label::Ptr continueLabel;
		tgui::Label::Ptr settingsLabel;
		tgui::Label::Ptr aboutLabel;
		tgui::Label::Ptr exitLabel;

	public:
		MenuScreen();
};