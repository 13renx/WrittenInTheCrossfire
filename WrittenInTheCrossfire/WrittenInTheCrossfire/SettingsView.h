#pragma once

#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class SettingsView : public View
{
	private:
		tgui::Label::Ptr titleLabel;
		tgui::Label::Ptr audioLabel;
		tgui::GrowVerticalLayout::Ptr leftLayout;
		tgui::Label::Ptr masterVolumeLabel;
		tgui::HorizontalLayout::Ptr masterVolumeLayout;
		tgui::Slider::Ptr masterVolumeSlider;
		tgui::Label::Ptr masterVolumeValueLabel;
		tgui::Label::Ptr backLabel;

	public:
		SettingsView(tgui::Gui& gui, ViewManager* viewManager);
};