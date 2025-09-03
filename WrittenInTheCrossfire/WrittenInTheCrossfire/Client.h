#pragma once
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

class Client {
    std::vector<json> history;
    json prompt;
    std::string apiKey;

    public:
        Client();
        void setApiKey(const std::string& key);
};