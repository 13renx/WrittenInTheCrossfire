#include "Fonts.h"
#include <TGUI/TGUI.hpp>

Fonts::Fonts() : title("Assets/Fonts/HomemadeApple.ttf"), writing("Assets/Fonts/Caveat.ttf") {
	tgui::Font::setGlobalFont("Assets/Fonts/Inconsolata.ttf");
}

tgui::Font& Fonts::getTitle() {
	return title;
}

tgui::Font& Fonts::getWriting() {
	return writing;
}