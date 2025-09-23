#include "Widgets.h"
#include "Macros.h"
#include <fmt/core.h>
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

tgui::Label::Ptr Widgets::Labels::createLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y) {
	tgui::Label::Ptr label = tgui::Label::create(text);

	label->setTextSize(textSize);
	label->setPosition(x, y);
	
	return label;
}

tgui::Label::Ptr Widgets::Labels::createButtonLabel(std::string text, unsigned int textSize, tgui::Layout x, tgui::Layout y, sf::Window* window) {
	tgui::Label::Ptr label = createLabel(text, textSize, x, y);

	label->onMouseEnter([=]() {
		window->setMouseCursor(sf::Cursor(sf::Cursor::Type::Hand));
		label->getRenderer()->setTextColor(tgui::Color::White);
	});
	label->onMouseLeave([=]() {
		window->setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		label->getRenderer()->setTextColor(Macros::Colors::Redwood);
	});
	
	return label;
}

tgui::Panel::Ptr Widgets::Panels::createPanel(const tgui::Texture& textureBackground) {
	tgui::Panel::Ptr panel = tgui::Panel::create();
	panel->getRenderer()->setTextureBackground(textureBackground);

	return panel;
}

tgui::Slider::Ptr Widgets::Sliders::createSlider() {
	tgui::Slider::Ptr slider = tgui::Slider::create();

	slider->setMaximum(100);
	slider->setValue(100);
	slider->setPosition(100, 0);

	return slider;
}

tgui::Slider::Ptr Widgets::Sliders::createVolumeSlider(tgui::Label::Ptr label) {
	tgui::Slider::Ptr slider = createSlider();

	slider->onValueChange([=](float value) {
		label->setText(fmt::format("{}", value));
	});

	return slider;
}