#pragma once

#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Client {
    std::string apiKey;
    json testPrompt;
    json gamePrompt;
    std::vector<json> history;

    public:
        Client();
        void setApiKey(const std::string& apiKey);
        json fetchResponse(const std::string& promptType);
};