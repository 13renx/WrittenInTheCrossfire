#pragma once

#include <map>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>

class Audio
{
	private:
		sf::Music music;
		bool isMusicRunning;
		std::map<std::string, sf::SoundBuffer> soundBuffers;
		std::map<std::string, sf::Sound> soundEffects;

	public:
		Audio();

		void playMusic();
		void stopMusic();
		void playSfx(std::string sfxName);
		void stopSfx(std::string sfxName);
};