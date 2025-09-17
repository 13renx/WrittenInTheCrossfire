#include "Widgets.h"
#include "Macros.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

tgui::Label::Ptr Widgets::Labels::createLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y) {
	tgui::Label::Ptr label = tgui::Label::create(text);
	label->setTextSize(textSize);
	label->setPosition(x, y);
	
	return label;
}

tgui::Label::Ptr Widgets::Labels::createButtonLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y) {
	tgui::Label::Ptr label = createLabel(text, textSize, x, y);

	label->onMouseEnter([=]() {
		label->getRenderer()->setTextColor(tgui::Color::White);
	});
	label->onMouseLeave([=]() {
		label->getRenderer()->setTextColor(Macros::Colors::Redwood);
	});
	
	return label;
}

tgui::Panel::Ptr Widgets::Panels::createPanel(const tgui::Texture& textureBackground) {
	tgui::Panel::Ptr panel = tgui::Panel::create();
	panel->getRenderer()->setTextureBackground(textureBackground);

	return panel;
}