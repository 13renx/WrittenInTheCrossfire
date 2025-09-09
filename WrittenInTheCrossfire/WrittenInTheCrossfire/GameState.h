#pragma once

#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameState {
    std::vector<json> chatHistory;
    int checkpoint;
    struct stats {
        int mentalWellbeing;
        int familyRelationship;
        int patriotism;
	} currentStats;

    public:
        std::vector<json> getChatHistory();
        void setChatHistory();
        int getCheckpoint();
        void setCheckpoint();
		stats getCurrentStats();
		void setCurrentStats();
};