#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Stats {
    int mentalWellbeing;
    int familyRelationship;
    int patriotism;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Stats, mentalWellbeing, familyRelationship, patriotism) // Creates to_json() and from_json() for Stats

struct MainSceneAsset {
    int checkpoint;
    std::string backgroundTexture;
    std::string dialogue;
};

struct LocationSceneAsset {
    int checkpoint;
    std::string backgroundTexture;
    std::string foregroundTexture;
    std::string dialogue;
};

struct NewspaperAsset {
    int checkpoint;
    std::string headline;
};