#include "Widgets.h"
#include "Macros.h"
#include "Model.h"
#include <fmt/core.h>
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Font.hpp>

tgui::Label::Ptr Widgets::Labels::createLabel(std::string text,
	unsigned int textSize,
	tgui::Layout x,
	tgui::Layout y,
	const tgui::Font& font)
{
	tgui::Label::Ptr label = tgui::Label::create(text);

	label->setTextSize(textSize);
	label->setPosition(x, y);

	label->getRenderer()->setFont(font);
	label->getRenderer()->setTextColor(Macros::Colors::Redwood);
	
	return label;
}

tgui::Label::Ptr Widgets::Labels::createButtonLabel(std::string text,
	unsigned int textSize,
	tgui::Layout x,
	tgui::Layout y,
	sf::RenderWindow& window,
	const tgui::Font& font)
{
	tgui::Label::Ptr label = createLabel(text, textSize, x, y, font);

	label->onMouseEnter([=, &window]() {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Hand));
		label->getRenderer()->setTextColor(tgui::Color::White);
	});
	label->onMouseLeave([=, &window]() {
		window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		label->getRenderer()->setTextColor(Macros::Colors::Redwood);
	});
	
	return label;
}

tgui::Panel::Ptr Widgets::Panels::createPanel(const tgui::Texture& textureBackground) {
	tgui::Panel::Ptr panel = tgui::Panel::create();
	panel->getRenderer()->setTextureBackground(textureBackground);

	return panel;
}

tgui::Panel::Ptr Widgets::Panels::createPanel(const tgui::Color& BackgroundColor) {
	tgui::Panel::Ptr panel = tgui::Panel::create();
	panel->getRenderer()->setBackgroundColor(BackgroundColor);

	return panel;
}

tgui::Slider::Ptr Widgets::Sliders::createSlider(int value) {
	tgui::Slider::Ptr slider = tgui::Slider::create();

	slider->setMaximum(100);
	slider->setValue(value);
	slider->setPosition(100, 0);

	return slider;
}

tgui::Slider::Ptr Widgets::Sliders::createVolumeSlider(tgui::Label::Ptr label, int volume) {
	tgui::Slider::Ptr slider = createSlider(volume);

	slider->onValueChange([=](float value) {
		label->setText(fmt::format("{}", value));
	});

	return slider;
}