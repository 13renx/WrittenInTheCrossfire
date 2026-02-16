#include "Audio.h"
#include "Utils.h"
#include <SFML/Audio.hpp>

Audio::Audio() {
	if(!music.openFromFile("./Assets/Audio/Music/witcmenu.mp3")) {
		isMusicRunning = true;
	} else {
		isMusicRunning = false;
	}

	soundBuffers = { 
		{ "paper", sf::SoundBuffer("./Assets/Audio/SFX/paper.mp3") } 
	};
	soundEffects = {
		{ "paper", sf::Sound(soundBuffers["paper"]) }
	};
}

void Audio::playMusic() {
	if(!isMusicRunning) {
		Utils::Log::info("Music played");
		music.play();
		music.setLooping(true);
		isMusicRunning = true;
	}
}

void Audio::stopMusic() {
	if(isMusicRunning) {
		Utils::Log::info("Music stopped");
		music.stop();
		isMusicRunning = false;
	}
}

void Audio::playSfx(std::string sfxName) {
	Utils::Log::info(fmt::format("{} sfx played", sfxName));
	soundEffects.at(sfxName).play();
}

void Audio::stopSfx(std::string sfxName) {
	Utils::Log::info(fmt::format("{} sfx stopped", sfxName));
	soundEffects.at(sfxName).stop();
}