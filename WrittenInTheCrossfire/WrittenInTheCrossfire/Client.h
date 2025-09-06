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

        enum class PromptType {
            TEST,
            GAME
        };

        enum class TestType {
            NO_API_KEY,
        };

        json fetchResponse(PromptType promptType, const std::string& apiKey);
        bool testApiKey(TestType testType, const std::string& apiKey);
        void setApiKey(const std::string& apiKey);
};