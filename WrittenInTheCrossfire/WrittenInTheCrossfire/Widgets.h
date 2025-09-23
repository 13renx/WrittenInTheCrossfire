#pragma once

#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Widgets {
	namespace Labels {
		tgui::Label::Ptr createLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y);
		tgui::Label::Ptr createButtonLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y, sf::Window* window);
	}

	namespace Panels {
		tgui::Panel::Ptr createPanel(const tgui::Texture& textureBackground);
	}

	namespace Sliders {
		tgui::Slider::Ptr createSlider();
		tgui::Slider::Ptr createVolumeSlider(tgui::Label::Ptr label);
	}
}