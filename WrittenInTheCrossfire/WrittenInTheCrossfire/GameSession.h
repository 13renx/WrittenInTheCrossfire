#pragma once

#include <vector>

using json = nlohmann::json;

class GameSession {
    std::vector<json> history;
}
