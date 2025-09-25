#pragma once

#include "Client.h"
#include "GameModel.h"
#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MenuView : public View
{
	private:
		Client& client;
		GameModel gameModel;

		tgui::Group::Ptr exitGroup;
		tgui::MessageBox::Ptr exitMessageBox;
		tgui::Panel::Ptr exitPanel;
		tgui::Group::Ptr apiGroup;
		tgui::ChildWindow::Ptr apiChildWindow;
		tgui::Panel::Ptr apiPanel;
		tgui::GrowVerticalLayout::Ptr apiMainLayout;
		tgui::GrowHorizontalLayout::Ptr apiButtonsLayout;
		tgui::Label::Ptr apiLabel;
		tgui::EditBox::Ptr apiEditBox;
		tgui::Group::Ptr apiFillerGroup;
		tgui::Button::Ptr apiEnterButton;
		tgui::Button::Ptr apiCancelButton;
		tgui::Label::Ptr titleLabel;
		tgui::GrowVerticalLayout::Ptr optionsLayout;
		tgui::Label::Ptr newGameLabel;
		tgui::Label::Ptr continueLabel;
		tgui::Label::Ptr settingsLabel;
		tgui::Label::Ptr aboutLabel;
		tgui::Label::Ptr exitLabel;

	public:
		MenuView(Client& client, tgui::Gui& gui, ViewManager* viewManager);
};