#include "Audio.h"

Audio::Audio() {
	if(!music.openFromFile("Assets/Audio/witcmenu.mp3")) {
		isMusicRunning = true;
	} else {
		isMusicRunning = false;
	}
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