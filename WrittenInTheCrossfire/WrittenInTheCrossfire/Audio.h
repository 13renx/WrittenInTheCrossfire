#pragma once

#include <SFML/Audio.hpp>

class Audio
{
	private:
		sf::Music music;
		bool isMusicRunning;
		
	public:
		Audio();

		void playMusic();
		void stopMusic();
};