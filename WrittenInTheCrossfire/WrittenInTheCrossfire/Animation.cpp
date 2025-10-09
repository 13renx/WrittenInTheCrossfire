#include "Animation.h"
#include <string>
#include <fmt/core.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

Animation::Animation(sf::Texture& texture, std::string framesDirectory, size_t totalFrames, float switchTime) : texture(texture) {
    activeFrame = 0;

    for(size_t i = 1; i <= totalFrames; i++) {
        frames.push_back(fmt::format("{}{}.png", framesDirectory, i));
	}

    totalTime = 0.0f;
    this->switchTime = switchTime;
}

void Animation::update(float deltaTime) {
    totalTime += deltaTime;

    if(totalTime >= switchTime) {
        totalTime -= switchTime;

        activeFrame++;

        if(activeFrame == frames.size()) {
            activeFrame = 0;
        }

        texture.loadFromFile(frames[activeFrame], false, sf::IntRect());
    }
}