#pragma once

#include "GameModel.h"
#include "View.h"
#include "ViewController.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class AboutView : public View
{
private:
	tgui::Label::Ptr titleLabel;
	tgui::Label::Ptr textLabel;
	tgui::Label::Ptr textLabel2;
	tgui::Label::Ptr textLabel3;
	tgui::Label::Ptr spacer;
	tgui::GrowVerticalLayout::Ptr leftLayout;
	tgui::GrowHorizontalLayout::Ptr buttonsLayout;
	tgui::Label::Ptr backLabel;

public:
	AboutView(ViewController* viewController, GameModel& gameModel);
};