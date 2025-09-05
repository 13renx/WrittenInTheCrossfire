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
        json fetchResponse(const std::string& promptType, const std::string& apiKey);
        bool testApiKey(const std::string& promptType, const std::string& apiKey);
        void setApiKey(const std::string& apiKey);
};