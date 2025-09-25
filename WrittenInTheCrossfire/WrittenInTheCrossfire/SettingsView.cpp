#include "SettingsView.h"
#include "SettingsModel.h"
#include "Widgets.h"
#include "View.h"
#include "ViewManager.h"
#include <memory>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

SettingsView::SettingsView(tgui::Gui& gui, ViewManager* viewManager) : View(gui, viewManager, "Assets/Textures/Backgrounds/Settings Page with other stuff.png") {
	settingsModel = SettingsModel();
	settingsModel.load();

	sf::Window* window = gui.getWindow();

	titleLabel = Widgets::Labels::createLabel("SETTINGS", 100, 700, 70);
	audioLabel = Widgets::Labels::createLabel("AUDIO", 75, 0, 0);
	leftLayout = tgui::GrowVerticalLayout::create(1000);
	masterVolumeLabel = Widgets::Labels::createLabel("MASTER VOLUME", 50, 0, 0);
	masterVolumeLayout = tgui::HorizontalLayout::create({ 600, 50 });
	masterVolumeValueLabel = Widgets::Labels::createLabel(std::to_string(settingsModel.getMasterVolume()), 25, 0, 0);
	masterVolumeSlider = Widgets::Sliders::createVolumeSlider(masterVolumeValueLabel, settingsModel.getMasterVolume());
	sfxVolumeLabel = Widgets::Labels::createLabel("SFX", 50, 0, 0);
	sfxVolumeLayout = tgui::HorizontalLayout::create({ 600, 50 });
	sfxVolumeValueLabel = Widgets::Labels::createLabel(std::to_string(settingsModel.getSfxVolume()), 25, 0, 0);
	sfxVolumeSlider = Widgets::Sliders::createVolumeSlider(sfxVolumeValueLabel, settingsModel.getSfxVolume());
	musicVolumeLabel = Widgets::Labels::createLabel("MUSIC", 50, 0, 0);
	musicVolumeLayout = tgui::HorizontalLayout::create({ 600, 50 });
	musicVolumeValueLabel = Widgets::Labels::createLabel(std::to_string(settingsModel.getMusicVolume()), 25, 0, 0);
	musicVolumeSlider = Widgets::Sliders::createVolumeSlider(musicVolumeValueLabel, settingsModel.getMusicVolume());
	backLabel = Widgets::Labels::createButtonLabel("BACK", 50, 0, 0, window);
	resetLabel = Widgets::Labels::createButtonLabel("RESET", 50, 0, 0, window);
	saveLabel = Widgets::Labels::createButtonLabel("SAVE", 50, 0, 0, window);
	buttonsLayout = tgui::GrowHorizontalLayout::create();
	
	leftLayout->setPosition(120, 200);
	buttonsLayout->setPosition(120, 930);
	buttonsLayout->getRenderer()->setSpaceBetweenWidgets(20);

	backLabel->onClick([=, &gui] {
		window->setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		this->viewManager->changeView(ViewManager::ViewType::MENU_VIEW);
	});
	resetLabel->onClick([=] {
		window->setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		settingsModel.init();
		masterVolumeValueLabel->setText(std::to_string(settingsModel.getMasterVolume()));
		masterVolumeSlider->setValue(settingsModel.getMasterVolume());
		sfxVolumeValueLabel->setText(std::to_string(settingsModel.getSfxVolume()));
		sfxVolumeSlider->setValue(settingsModel.getSfxVolume());
		musicVolumeValueLabel->setText(std::to_string(settingsModel.getMusicVolume()));
		musicVolumeSlider->setValue(settingsModel.getMusicVolume());
	});
	saveLabel->onClick([=] {
		window->setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
		settingsModel.setMasterVolume(std::stoi(masterVolumeValueLabel->getText().toStdString()));
		settingsModel.setSfxVolume(std::stoi(sfxVolumeValueLabel->getText().toStdString()));
		settingsModel.setMusicVolume(std::stoi(musicVolumeValueLabel->getText().toStdString()));
		settingsModel.save();
	});

	mainPanel->add(titleLabel);
	mainPanel->add(leftLayout);
	mainPanel->add(buttonsLayout);
	leftLayout->add(audioLabel);
	leftLayout->add(masterVolumeLabel);
	leftLayout->add(masterVolumeLayout);
	leftLayout->add(sfxVolumeLabel);
	leftLayout->add(sfxVolumeLayout);
	leftLayout->add(musicVolumeLabel);
	leftLayout->add(musicVolumeLayout);
	masterVolumeLayout->add(masterVolumeSlider);
	masterVolumeLayout->add(masterVolumeValueLabel);
	sfxVolumeLayout->add(sfxVolumeSlider);
	sfxVolumeLayout->add(sfxVolumeValueLabel);
	musicVolumeLayout->add(musicVolumeSlider);
	musicVolumeLayout->add(musicVolumeValueLabel);
	buttonsLayout->add(backLabel);
	buttonsLayout->add(resetLabel);
	buttonsLayout->add(saveLabel);
	gui.add(mainPanel);
}

