#pragma once

#include "witc.h"
#include <string>
#include <tuple>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameState {
    std::vector<json> chatHistory;
    int checkpoint;
    witc::stats currentStats;

    public:
        GameState();
        
        std::vector<json> getChatHistory();
        void setChatHistory(std::vector<json> chatHistory);
        int getCheckpoint();
        void setCheckpoint(int checkpoint);
		witc::stats getCurrentStats();
		void setCurrentStats(witc::stats currentStats);
        std::tuple<bool, std::string> save(); // Saves game state to save file (save.json)
        std::tuple<bool, std::string> load(); // Loads game state from save file (save.json)
};