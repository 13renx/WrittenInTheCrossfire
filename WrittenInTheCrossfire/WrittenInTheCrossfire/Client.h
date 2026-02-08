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

    public:
        Client();

        std::string getApiKey();
        json fetchResponse(PromptType promptType, const std::string& apiKey);
        std::tuple<bool, std::string> testApiKey(const std::string& apiKey);
        void setApiKey(const std::string& apiKey);
        void setGamePromptContents(std::vector<json>& j);
};