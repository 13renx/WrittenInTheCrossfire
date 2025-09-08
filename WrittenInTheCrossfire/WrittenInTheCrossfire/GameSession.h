#pragma once

#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameSession {
    std::vector<json> history;
}
