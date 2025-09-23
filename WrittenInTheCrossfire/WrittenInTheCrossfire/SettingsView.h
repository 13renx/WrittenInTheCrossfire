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
		tgui::Label::Ptr sfxVolumeLabel;
		tgui::HorizontalLayout::Ptr sfxVolumeLayout;
		tgui::Slider::Ptr sfxVolumeSlider;
		tgui::Label::Ptr sfxVolumeValueLabel;
		tgui::Label::Ptr musicVolumeLabel;
		tgui::HorizontalLayout::Ptr musicVolumeLayout;
		tgui::Slider::Ptr musicVolumeSlider;
		tgui::Label::Ptr musicVolumeValueLabel;
		tgui::GrowHorizontalLayout::Ptr buttonsLayout;
		tgui::Label::Ptr backLabel;
		tgui::Label::Ptr resetLabel;
		tgui::Label::Ptr saveLabel;

	public:
		SettingsView(tgui::Gui& gui, ViewManager* viewManager);
};