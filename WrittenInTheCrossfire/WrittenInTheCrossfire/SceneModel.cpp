#include "SceneModel.h"
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <fmt/core.h>

SceneModel::SceneModel() {
    std::ifstream file = std::ifstream("Story.txt");
    std::string line;
    int checkpoint = -4;
    std::string texture = "EMPTY";
    std::string dialogue = "EMPTY";

    // Extract assets data from "Story.txt"
    while(std::getline(file, line)) {
        std::tuple<int, std::string, std::string> asset;

        if(line.size() < 2) { // Empty line
            texture = "EMPTY";
            dialogue = "EMPTY";
        }
        else if(line.starts_with("Act")) {
            checkpoint = -4;
            texture = "EMPTY";
            dialogue = "EMPTY";
        }
        else if(line.starts_with("Week")) { // Checkpoint
            line.erase(0, 5); // Remove "Week "
            checkpoint = std::stoi(line);
            texture = "EMPTY";
        }
        else if(line.size() > 3) {
            if(line.at(0) >= '0' && line.at(0) <= '9') { // Texture
                if(line.find("Black Screen") != std::string::npos) {
                    texture = "";
                }
                else {
                    if(line.at(1) >= '0' && line.at(1) <= '9') {
                        line.erase(0, 4); // Remove "10. "
                    }
                    else {
                        line.erase(0, 3); // Remove "1. "
                    }

                    line.pop_back(); // Remove semicolon
                    line.append(".png");
                    texture = fmt::format("./Assets/Textures/Scenes/{}", line);
                }

                dialogue = "EMPTY";
            }
            else if(line.starts_with("   ")) { // Dialogue
                line.erase(0, 3); // Remove "   "

                if(line.at(1) >= '0' && line.at(1) <= '9') {
                    line.erase(0, 4); // Remove "10. "
                }
                else {
                    line.erase(0, 3); // Remove "1. "
                }

                dialogue = line;
            }
        }

        if(checkpoint != -4 && texture != "EMPTY" && dialogue != "EMPTY") {
            assets.push_back(std::make_tuple(checkpoint, texture, dialogue));
        }
    }
}

std::vector<std::tuple<int, std::string, std::string>> SceneModel::getCheckpointAssets(int checkpoint) {
    std::vector<std::tuple<int, std::string, std::string>> ret;

    for(const auto& asset : assets) {
        if(std::get<0>(asset) == checkpoint) {
            ret.push_back(asset);
        }
    }

    return ret;
}