#pragma once

#include <string>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Animation {
    private:
        sf::Texture& texture;
        std::vector<std::string> frames;
        size_t activeFrame;
        float totalTime;
        float switchTime;
    
    public:
        Animation(sf::Texture& texture, std::string framesDirectory, size_t totalFrames, float switchTime);

        void update(float deltaTime);
};