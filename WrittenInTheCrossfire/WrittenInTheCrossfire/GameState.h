#pragma once

#include <vector>

using json = nlohmann::json;

class GameState {
    std::vector<json> chatHistory;
    int checkpoint;
}
