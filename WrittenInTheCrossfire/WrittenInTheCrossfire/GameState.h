#pragma once

#include <vector>

using json = nlohmann::json;

class GameState {
    std::vector<json> chatHistory;
    int checkpoint;
    
    public:
        std::vector<json> getChatHistory();
        void setChatHistory();
        int getCheckpoint();
        void setCheckpoint();
}
