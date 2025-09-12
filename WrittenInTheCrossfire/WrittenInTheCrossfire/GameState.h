#pragma once

#include "witc.h"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameState {
    std::vector<json> chatHistory;
    int checkpoint;
    witc::stats currentStats;

    public:
        std::vector<json> getChatHistory();
        void setChatHistory(std::vector<json> chatHistory);
        int getCheckpoint();
        void setCheckpoint(int checkpoint);
		witc::stats getCurrentStats();
		void setCurrentStats(witc::stats currentStats);
		void save(); // Save game state to save file (save.json)
		void load(); // Load game state from save file (save.json)
};