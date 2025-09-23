#include "SettingsModel.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

SettingsModel::SettingsModel() {
	init();
}

void SettingsModel::init() {
	masterVolume = 100;
	sfxVolume = 100;
	musicVolume = 100;
}

int SettingsModel::getMasterVolume() {
	return masterVolume;
}

void SettingsModel::setMasterVolume(int volume) {
	masterVolume = volume;
}

int SettingsModel::getSfxVolume() {
	return sfxVolume;
}

void SettingsModel::setSfxVolume(int volume) {
	sfxVolume = volume;
}

int SettingsModel::getMusicVolume() {
	return musicVolume;
}

void SettingsModel::setMusicVolume(int volume) {
	musicVolume = volume;
}

std::tuple<bool, std::string> SettingsModel::save() {
	json save = *this;
	std::ofstream file = std::ofstream("settings.json");

	if(file.is_open()) {
		file << save.dump(4) << std::endl;
		return { true, "Settings saved successfully." };
	}
	else {
		return { false, "Failed to save settings." };
	}
}

std::tuple<bool, std::string> SettingsModel::load() {
	json load;
	std::ifstream file = std::ifstream("settings.json");

	if(file.is_open()) {
		file >> load;
		auto settingsModel = load.template get<SettingsModel>();

		setMasterVolume(settingsModel.getMasterVolume());
		setSfxVolume(settingsModel.getSfxVolume());
		setMusicVolume(settingsModel.getMusicVolume());

		return { true, "Settings loaded successfully." };
	} else {
		init();
		save();
		return { false, "Failed to load settings." };
	}
}