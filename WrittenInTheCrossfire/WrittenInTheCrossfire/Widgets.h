#pragma once

#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Widgets {
	namespace Labels {
		tgui::Label::Ptr createLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y, const tgui::Font& font);
		tgui::Label::Ptr createButtonLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y, sf::RenderWindow& window, const tgui::Font& font);
	}

	namespace Panels {
		tgui::Panel::Ptr createPanel(const tgui::Texture& textureBackground);
		tgui::Panel::Ptr createPanel(const tgui::Color& BackgroundColor);
	}

	namespace Sliders {
		tgui::Slider::Ptr createSlider(int value);
		tgui::Slider::Ptr createVolumeSlider(tgui::Label::Ptr label, int volume);
	}
}