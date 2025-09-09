#pragma once

#include "Stats.h"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameState {
    std::vector<json> chatHistory;
    int checkpoint;
    stats currentStats;

    public:
        std::vector<json> getChatHistory();
        void setChatHistory(std::vector<json> chatHistory);
        int getCheckpoint();
        void setCheckpoint(int checkpoint);
		stats getCurrentStats();
		void setCurrentStats(stats currentStats);
};