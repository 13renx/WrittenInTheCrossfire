#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Widgets {
	namespace Label {
		tgui::Label::Ptr createNormalLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y);
		tgui::Label::Ptr createButtonLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y);
	}

	namespace Panel {
		tgui::Panel::Ptr createNormalPanel(const tgui::Texture& textureBackground);
	}
}