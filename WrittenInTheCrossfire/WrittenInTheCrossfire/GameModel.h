#pragma once

#include "Model.h"
#include "Stats.h"
#include <string>
#include <tuple>
#include <vector>
#include <nlohmann/json.hpp>

class GameModel : Model {
    private:
        std::vector<json> chatHistory;
        int checkpoint;
        Stats currentStats;

    public:
        GameModel();
        
        void init() override;
        std::vector<json> getChatHistory();
        void setChatHistory(std::vector<json> chatHistory);
        int getCheckpoint();
        void setCheckpoint(int checkpoint);
        Stats getCurrentStats();
        void setCurrentStats(Stats currentStats);
        std::tuple<bool, std::string> save() override; // Saves game model to save file (game.json)
        std::tuple<bool, std::string> load() override; // Loads game model from save file (game.json)

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameModel, chatHistory, checkpoint, currentStats) // Creates to_json() and from_json() for GameModel
};