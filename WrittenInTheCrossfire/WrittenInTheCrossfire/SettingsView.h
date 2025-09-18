#pragma once

#include "View.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class SettingsView : public View
{
	private:
		tgui::Label::Ptr titleLabel;

	public:
		SettingsView(tgui::Gui& gui, std::shared_ptr<View> activeView);
};