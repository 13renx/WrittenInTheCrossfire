#pragma once

#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class SettingsView : public View
{
	private:
		tgui::Label::Ptr backLabel;
		tgui::Label::Ptr titleLabel;

	public:
		SettingsView(tgui::Gui& gui, ViewManager* viewManager);
};