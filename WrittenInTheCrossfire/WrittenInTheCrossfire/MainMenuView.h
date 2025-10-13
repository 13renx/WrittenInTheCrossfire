#pragma once

#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MainMenuView : public View
{
	private:
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
		tgui::Label::Ptr optionsNewGameLabel;
		tgui::Label::Ptr optionsContinueLabel;
		tgui::Label::Ptr optionsSettingsLabel;
		tgui::Label::Ptr optionsAboutLabel;
		tgui::Label::Ptr optionsExitLabel;

	public:
		MainMenuView(ViewController* viewController, GameModel& gameModel);
};