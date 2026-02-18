#pragma once

#include "Model.h"
#include "Structs.h"
#include <string>
#include <tuple>
#include <vector>
#include <nlohmann/json.hpp>

class GameState : Model {
    private:
        std::vector<json> chatHistory;
        int checkpoint;
        Stats currentStats;
        bool isLocationVisited

    public:
        GameState();
        
        void init() override;
        std::vector<json> getChatHistory();
        void setChatHistory(std::vector<json> chatHistory);
        int getCheckpoint();
        void setCheckpoint(int checkpoint);
        Stats& getCurrentStats();
        void setCurrentStats(Stats& currentStats);
        std::tuple<bool, std::string> save() override;
        std::tuple<bool, std::string> load() override;
        void incrementCheckpoint();
		Stats calculateStatChanges(json& sentiments);
        void updateCurrentStats(json& sentiments);

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameState, chatHistory, checkpoint, currentStats) // Creates to_json() and from_json() for GameState
};