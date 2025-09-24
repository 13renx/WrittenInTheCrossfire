#pragma once

#include "GameModel.h"
#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MenuView : public View
{
	private:
		GameModel gameModel;

		tgui::Group::Ptr exitGroup;
		tgui::MessageBox::Ptr exitMessageBox;
		tgui::Panel::Ptr exitPanel;
		tgui::ChildWindow::Ptr apiChildWindow;
		tgui::EditBox::Ptr apiEditBox;
		tgui::Label::Ptr titleLabel;
		tgui::GrowVerticalLayout::Ptr optionsLayout;
		tgui::Label::Ptr newGameLabel;
		tgui::Label::Ptr continueLabel;
		tgui::Label::Ptr settingsLabel;
		tgui::Label::Ptr aboutLabel;
		tgui::Label::Ptr exitLabel;

	public:
		MenuView(tgui::Gui& gui, ViewManager* viewManager);
};