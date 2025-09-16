#pragma once

#include <string>
#include <tuple>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Client {
    private:
        std::string apiKey;
        json testPrompt;
        json gamePrompt;

    public:
        enum class PromptType {
            TEST,
            GAME
        };

        enum class TestType {
            NO_API_KEY,
            WITH_API_KEY
        };

    public:
        Client();

        json fetchResponse(PromptType promptType, const std::string& apiKey);
        std::tuple<bool, std::string>  testApiKey(TestType testType, const std::string& apiKey);
        std::tuple<bool, std::string> setApiKey(const std::string& apiKey);
};