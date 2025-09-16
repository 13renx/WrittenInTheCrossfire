#pragma once

#include "View.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MenuView : public View
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
		MenuView(tgui::Gui& g, std::shared_ptr<View> v);
};