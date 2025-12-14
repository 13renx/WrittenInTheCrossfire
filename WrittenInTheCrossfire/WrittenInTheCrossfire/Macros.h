#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Macros {
	namespace Colors {
		constexpr inline tgui::Color Redwood{ 180, 120, 105 }; // Label text color
		constexpr inline tgui::Color Grey{ 128, 128, 128 }; // Label text color when clicked
		constexpr inline tgui::Color TransparentGrey{ 128, 128, 128, 60 }; // Dialog box color
	};
	namespace Fonts {
		// Functions hold and return the same instance of their respective tgui::Font objects
		inline const tgui::Font& Title()
		{
			static const tgui::Font font("Assets/Fonts/HomemadeApple.ttf");
			return font;
		}
		inline const tgui::Font& Writing()
		{
			static const tgui::Font font("Assets/Fonts/Caveat.ttf");
			return font;
		}
		inline const tgui::Font& Default()
		{
			static const tgui::Font font("Assets/Fonts/Inconsolata.ttf");
			return font;
		}
	};
}