#include "StoryModel.h"
#include "Structs.h"
#include <fstream>
#include <vector>
#include "fmt/core.h"

StoryModel::StoryModel() {
    std::ifstream file = std::ifstream("Story.txt");
    std::string line;

    int checkpoint = 0;
    bool isMainScene = false;
    bool isLocationScene = false;
    bool isNewspaper = false;

    MainSceneAsset mainSceneAsset;
    mainSceneAsset.checkpoint = 0;
    mainSceneAsset.backgroundTexture = "";
    mainSceneAsset.dialogue = "";
    LocationSceneAsset locationSceneAsset;
    locationSceneAsset.checkpoint = 0;
    locationSceneAsset.backgroundTexture = "";
    locationSceneAsset.dialogue = "";
    NewspaperAsset newspaper;
    newspaper.checkpoint = 0;
    newspaper.headline = "";

    while(std::getline(file, line)) {
        if(line.starts_with("Week")) {
            line.erase(0, 5); // Remove "Week "
            checkpoint = std::stoi(line);

            mainSceneAsset.checkpoint = checkpoint;
            locationSceneAsset.checkpoint = checkpoint;
            newspaper.checkpoint = checkpoint;
        }

        if(isMainScene && line.size() > 3) {
            if(line.at(0) >= '0' && line.at(0) <= '9') { // backgroundTexture
                if(line.find("Black Screen") != std::string::npos) {
                    mainSceneAsset.backgroundTexture = "";
                } else{
                    if(line.at(1) >= '0' && line.at(1) <= '9') {
                        line.erase(0, 4); // Remove "10. "
                    } else {
                        line.erase(0, 3); // Remove "1. "
                    }

                    line.pop_back(); // Remove colon
                    line.append(".png");
                    mainSceneAsset.backgroundTexture = fmt::format("./Assets/Textures/Scenes/{}", line);
                }

                mainSceneAsset.dialogue = "";
            } else if(line.starts_with("   ")) { // Dialogue
                line.erase(0, 3); // Remove "   "

                if(line.at(1) >= '0' && line.at(1) <= '9') {
                    line.erase(0, 4); // Remove "10. "
                } else{
                    line.erase(0, 3); // Remove "1. "
                }

                mainSceneAsset.dialogue = line;
            }

            if(mainSceneAsset.dialogue != "") {
                mainSceneAssets.push_back(mainSceneAsset);
            }
        }
        else if(isLocationScene && line.size() > 3) {
            if(line.starts_with("Bunk 1")) {
                locationSceneAsset.backgroundTexture = "./Assets/Textures/Scenes/Bunker.png";
                locationSceneAsset.foregroundTexture = "";
                locationSceneAsset.dialogue = "";
            } else if(line.starts_with("Eating")) {
                locationSceneAsset.backgroundTexture = "./Assets/Textures/Scenes/Meal Time Morning.png";
                locationSceneAsset.foregroundTexture = "";
                locationSceneAsset.dialogue = "";
            } else if(line.starts_with("Bunk 2")) {
                locationSceneAsset.backgroundTexture = "./Assets/Textures/Scenes/Storage Bunker.png";
                locationSceneAsset.foregroundTexture = "";
                locationSceneAsset.dialogue = "";
            } else if(line.at(0) >= '0' && line.at(0) <= '9') { // foregroundTexture
                if(line.find("Black Screen") != std::string::npos) {
                    locationSceneAsset.foregroundTexture = "";
                } else{
                    if(line.at(1) >= '0' && line.at(1) <= '9') {
                        line.erase(0, 4); // Remove "10. "
                    } else {
                        line.erase(0, 3); // Remove "1. "
                    }

                    line.pop_back(); // Remove colon
                    line.append(".png");
                    locationSceneAsset.foregroundTexture = fmt::format("./Assets/Textures/Scenes/{}", line);
                }

                locationSceneAsset.dialogue = "";
            } else if(line.starts_with("   ")) { // Dialogue
                line.erase(0, 3); // Remove "   "

                if(line.at(1) >= '0' && line.at(1) <= '9') {
                    line.erase(0, 4); // Remove "10. "
                } else{
                    line.erase(0, 3); // Remove "1. "
                }

                locationSceneAsset.dialogue = line;
            }

            if(locationSceneAsset.foregroundTexture != "" && locationSceneAsset.dialogue != "") {
                locationSceneAssets.push_back(locationSceneAsset);
            }
        }
        else if(isNewspaper && line.size() > 3) {
            line.erase(0, 5); // Remove "   1. "
            newspaper.headline = line;
            newspaperAssets.push_back(newspaper);
            isNewspaper = false;
        }

        if(line.starts_with("Slides")) {
            isMainScene = true;
            isNewspaper = false;
        }
        else if(line.starts_with("Location")) {
            isLocationScene = true;
            isMainScene = false;
        }
        else if(line.starts_with("1. Main")) {
            isNewspaper = true;
            isLocationScene = false;
        }
    }

    file.close();
}

std::vector<MainSceneAsset> StoryModel::getMainSceneAssets(int checkpoint) {
    std::vector<MainSceneAsset> ret;

    for(const auto& mainSceneAsset : mainSceneAssets) {
        if(mainSceneAsset.checkpoint == checkpoint) {
            ret.push_back(mainSceneAsset);
        }
    }

    return ret;
}

std::vector<LocationSceneAsset> StoryModel::getLocationSceneAssets(int checkpoint) {
    std::vector<LocationSceneAsset> ret;

    for(const auto& locationSceneAsset : locationSceneAssets) {
        if(locationSceneAsset.checkpoint == checkpoint) {
            ret.push_back(locationSceneAsset);
        }
    }

    return ret;
}

std::vector<NewspaperAsset> StoryModel::getNewspaperAssets(int checkpoint) {
    std::vector<NewspaperAsset> ret;

    for(const auto& newspaperAsset : newspaperAssets) {
        if(newspaperAsset.checkpoint == checkpoint) {
            ret.push_back(newspaperAsset);
        }
    }

    return ret;
}