#define _CRT_SECURE_NO_WARNINGS

#include "Client.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Client::Client() {
	this->testPrompt = json::parse(R"(
		{ 
			"contents": [
				{ 
					"parts": [
						{
							"text": "test"
						}	
					]
				}
			] 
		}
	)");
}

void Client::setApiKey(const std::string& apiKey) {
	this->apiKey = apiKey;
}

void Client::fetchResponse(const std::string& promptType) {
	if(promptType == "test") {

	}
	else if(promptType == "normal") {

	}
}