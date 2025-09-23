#pragma once

#include "Model.h"
#include "Stats.h"
#include <string>
#include <tuple>
#include <nlohmann/json.hpp>

class SettingsModel : Model
{
	private:
		int masterVolume;
		int sfxVolume;
		int musicVolume;

	public:
		SettingsModel();

		void init() override;
		int getMasterVolume();
		void setMasterVolume(int volume);
		int getSfxVolume();
		void setSfxVolume(int volume);
		int getMusicVolume();
		void setMusicVolume(int volume);
		std::tuple<bool, std::string> save() override;
		std::tuple<bool, std::string> load() override;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SettingsModel, masterVolume, sfxVolume, musicVolume) // Creates to_json() and from_json() for GameModel
};