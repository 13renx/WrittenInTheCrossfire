#pragma once

#include "View.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class SettingsView : public View
{
	private:
		tgui::Label::Ptr titleLabel;

	public:
		SettingsView(tgui::Gui& g, std::shared_ptr<View> v);
};