#include "Audio.h"
#include <SFML/Audio.hpp>

Audio::Audio() {
	if(!music.openFromFile("Assets/Audio/witcmenu.mp3")) {
		isMusicRunning = true;
	} else {
		isMusicRunning = false;
	}

	soundBuffers = { 
		{ "paper", sf::SoundBuffer("Assets/Audio/SFX/paper.mp3") } 
	};
	soundEffects = {
		{ "paper", sf::Sound(soundBuffers["paper"]) }
	};
}

void Audio::playMusic() {
	if(!isMusicRunning) {
		music.play();
		music.setLooping(true);
		isMusicRunning = true;
	}
}

void Audio::stopMusic() {
	if(isMusicRunning) {
		music.stop();
		isMusicRunning = false;
	}
}

void Audio::playSfx(std::string sfxName) {
	soundEffects.at(sfxName).play();
}

void Audio::stopSfx(std::string sfxName) {
	soundEffects.at(sfxName).stop();
}