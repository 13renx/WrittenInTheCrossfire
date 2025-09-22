#include "SettingsView.h"
#include "Widgets.h"
#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

SettingsView::SettingsView(tgui::Gui& gui, ViewManager* viewManager) : View(viewManager) {
	sf::Window* window = gui.getWindow();

	mainPanel = Widgets::Panels::createPanel("Assets/Textures/Backgrounds/Settings Page with other stuff.png");
	titleLabel = Widgets::Labels::createLabel("SETTINGS", 100, 700, 70);
	audioLabel = Widgets::Labels::createLabel("AUDIO", 75, 0, 0);
	leftLayout = tgui::GrowVerticalLayout::create(1000);
	masterVolumeLabel = Widgets::Labels::createLabel("MASTER VOLUME", 50, 0, 0);
	masterVolumeLayout = tgui::HorizontalLayout::create({ 600, 50 });
	masterVolumeSlider = tgui::Slider::create();
	masterVolumeValueLabel = Widgets::Labels::createLabel("100", 25, 0, 0);
	backLabel = Widgets::Labels::createButtonLabel("BACK", 50, 120, 930, window);
	
	leftLayout->setPosition(120, 200);
	masterVolumeSlider->setMaximum(100);
	masterVolumeSlider->setValue(100);
	
	masterVolumeSlider->onValueChange([=](float value) {
		masterVolumeValueLabel->setText(fmt::format("{}", value));
	});
	backLabel->onClick([=, &gui] {
		window->setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewManager->changeView(ViewManager::ViewType::MENU_VIEW);
	});

	mainPanel->add(titleLabel);
	leftLayout->add(audioLabel);
	leftLayout->add(masterVolumeLabel);
	masterVolumeLayout->add(masterVolumeSlider);
	masterVolumeLayout->add(masterVolumeValueLabel);
	leftLayout->add(masterVolumeLayout);
	mainPanel->add(leftLayout);
	mainPanel->add(backLabel);
	gui.add(mainPanel);
}

