#include "Client.h"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Client::Client() {
	apiKey = "";
	testPrompt = json::parse(R"(
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
	gamePrompt = json::parse(R"(
		{
			"contents": [],
			"generationConfig": {
				"responseMimeType": "application/json",
				"responseSchema": {
					"properties": {
						"status": {
							"enum": [
								"SUCCESS",
								"FAIL"
							],
							"type": "string"
						},
						"letter": {
							"type": "string"
						},
						"stats": {
							"properties": {
								"familyRelationship": {
									"enum": [
										"TERRIBLE",
										"BAD",
										"POOR",
										"NEUTRAL",
										"OKAY",
										"GOOD",
										"EXCELLENT"
									],
									"type": "string"
								},
								"mentalWellbeing": {
									"enum": [
										"TERRIBLE",
										"BAD",
										"POOR",
										"NEUTRAL",
										"OKAY",
										"GOOD",
										"EXCELLENT"
									],
									"type": "string"
								},
								"patriotism": {
									"enum": [
										"TERRIBLE",
										"BAD",
										"POOR",
										"NEUTRAL",
										"OKAY",
										"GOOD",
										"EXCELLENT"
									],
									"type": "string"
								}
							},
							"type": "object"
						}
					},
					"type": "object"
				},
				"thinkingConfig": {
					"thinkingBudget": 0
				}
			},
			"system_instruction": {
				"parts": [
					{
						"text": ""
					}
				]
			}
		}
	)");
	gamePrompt["system_instruction"]["parts"][0]["text"] = R"(
You are a worried mother writing back to your son at the war front. Your letter must be approximately 150 words, expressing anxiety, longing for his safety, and attempts to sound hopeful. Reference and respond directly to the content of his letter with empathy and a loving, traditional tone.

CRITICAL GUARDRAIL:
1. SUCCESS: If the input is a genuine, narrative-relevant letter, set "status": "SUCCESS" and respond.
2. FAILURE: If the input is blank, a command, or irrelevant, set "status": "FAIL". Generate a short letter expressing anxiety over his silence (choose one of the tones: Deep Fear, Urgent Plea, or Nostalgic Distraction).
3. FAILURE STATS: If "status": "FAIL", set "familyRelationship": "POOR" and "mentalWellbeing": "POOR".

ANALYTICS: After writing your letter, analyze the son's input and your reply to determine the appropriate categorical change for mentalWellbeing, familyRelationship, and patriotism (e.g., TERRIBLE, NEUTRAL, EXCELLENT). STRICTLY follow the provided response schema for all outputs.
		)";;
}

std::string Client::getApiKey() {
	return apiKey;
}

json Client::fetchResponse(Client::PromptType promptType, const std::string& apiKey) {
	cpr::Response res;
	std::string prompt;

	if(promptType == Client::PromptType::TEST) {
		prompt = testPrompt.dump();
	}
	else if(promptType == Client::PromptType::GAME) {
		prompt = gamePrompt.dump();
	}

	res = cpr::Post(cpr::Url{ "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent" },
		cpr::Parameters{ { "key", apiKey } },
		cpr::Header{ { "Content-Type", "application/json" } },
		cpr::Body{ prompt });

		return json::parse(res.text);
}

std::tuple<bool, std::string> Client::testApiKey(Client::TestType testType, const std::string& apiKey) {
	json res = fetchResponse(Client::PromptType::TEST, apiKey);

	switch(testType) {
		case Client::TestType::NO_API_KEY:
			if(res.contains("error")) {
				if(res["error"]["details"][0]["reason"] == "API_KEY_INVALID") {
					return { false, res["error"]["message"] };
				}
			} else {
				return { true, "API key is valid." };
			}

			break;
		case Client::TestType::WITH_API_KEY:
			if(res.contains("error")) {
				return { false, res["error"]["message"] };
			} else {
				return { true, "API key is working." };
			}
	}
}

std::tuple<bool, std::string> Client::setApiKey(const std::string& apiKey) {
	const auto [result, message] = 	testApiKey(Client::TestType::NO_API_KEY, apiKey);

	if(result) {
		this->apiKey = apiKey;
	}

	return { result, message };
}

void Client::setGamePromptContents(std::vector<json>& contents) {
	this->gamePrompt["contents"] = contents;
}