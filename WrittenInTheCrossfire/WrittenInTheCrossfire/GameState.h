#pragma once

#include "Stats.h"
#include <string>
#include <tuple>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameState {
    std::vector<json> chatHistory;
    int checkpoint;
    Stats currentStats;

    public:
        GameState();
        
        std::vector<json> getChatHistory();
        void setChatHistory(std::vector<json> chatHistory);
        int getCheckpoint();
        void setCheckpoint(int checkpoint);
        Stats getCurrentStats();
        void setCurrentStats(Stats currentStats);
        std::tuple<bool, std::string> save(); // Saves game state to save file (save.json)
        std::tuple<bool, std::string> load(); // Loads game state from save file (save.json)

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameState, chatHistory, checkpoint, currentStats) // Creates to_json() and from_json() for GameState
};