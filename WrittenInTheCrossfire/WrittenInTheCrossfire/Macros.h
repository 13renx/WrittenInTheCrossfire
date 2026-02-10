#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Macros {
	namespace Colors {
		constexpr inline tgui::Color Redwood{ 180, 120, 105 }; // Label text color
		constexpr inline tgui::Color Grey{ 128, 128, 128 }; // Label text color when clicked
		constexpr inline tgui::Color TransparentGrey{ 57, 57, 57, 150 }; // Dialog box color
	};
}