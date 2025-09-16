#pragma once

#include "Screen.h"
#include "MenuScript.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MenuScreen : public Screen
{
	private:
		tgui::GrowVerticalLayout::Ptr layout;
		tgui::Label::Ptr titleLabel;
		tgui::Label::Ptr newGameLabel;
		tgui::Label::Ptr continueLabel;
		tgui::Label::Ptr settingsLabel;
		tgui::Label::Ptr aboutLabel;
		tgui::Label::Ptr exitLabel;
		tgui::Panel::Ptr exitPanel;
		tgui::MessageBox::Ptr exitMessageBox;
		tgui::Group::Ptr exitGroup;

	public:
		MenuScreen(tgui::Gui& g);

		void stylize();
		void functionalize();
};