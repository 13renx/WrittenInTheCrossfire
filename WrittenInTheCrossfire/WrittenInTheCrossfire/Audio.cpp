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
		{ "letter", sf::SoundBuffer("./Assets/Audio/SFX/letter.mp3") } 
	};
	soundEffects = {
		{ "letter", sf::Sound(soundBuffers["letter"]) }
	};
}

void Audio::playMusic() {
	if(!isMusicRunning) {
		Utils::Log::debugInfo("Music played");
		music.play();
		music.setLooping(true);
		isMusicRunning = true;
	}
}

void Audio::stopMusic() {
	if(isMusicRunning) {
		Utils::Log::debugInfo("Music stopped");
		music.stop();
		isMusicRunning = false;
	}
}

void Audio::playSfx(std::string sfxName) {
	Utils::Log::debugInfo(fmt::format("{} sfx played", sfxName));
	soundEffects.at(sfxName).play();
}

void Audio::stopSfx(std::string sfxName) {
	Utils::Log::debugInfo(fmt::format("{} sfx stopped", sfxName));
	soundEffects.at(sfxName).stop();
}