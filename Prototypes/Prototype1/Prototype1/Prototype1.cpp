#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <dotenv.h>
#include <cpr/cpr.h>
#include <fmt/base.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void printInstructions();

int main()
{
	dotenv::init(".env");
	const char* apiKeyTemp = std::getenv("API_KEY");	

	if (apiKeyTemp == nullptr) {
		throw std::runtime_error("API_KEY was not found");
	}

	const std::string apiKey = std::string(apiKeyTemp);

	std::string input;
	json data;
	json output;
	std::string outputText;

	fmt::print("Terminal AI Chatbot using C++ and Gemini API\n");
	printInstructions();

	do {
		fmt::print("> ");
		std::getline(std::cin, input);

		if (input == "help") {
			printInstructions();
		}
		else if (input == "exit") {
			fmt::print("Thanks for using the chatbot!\n");
			break;
		}
		else if (input != "") {
			data = json::parse(R"(
				{ 
					"contents": [
						{ 
							"parts": []
						}
					] 
				}
			)");
			data["contents"][0]["parts"][0]["text"] = input;
			
			cpr::Response res = cpr::Post(cpr::Url{ "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent" },
				cpr::Parameters{ { "key", apiKey } },
				cpr::Header{ { "Content-Type", "application/json" } },
				cpr::Body{ data.dump() });

			// Add error handling for response

			output = json::parse(res.text);
			outputText = output["candidates"][0]["content"]["parts"][0]["text"].template get<std::string>();
			fmt::print("{}\n", outputText);
		}
	} while (true);

	return 0;
}

void printInstructions() {
	fmt::print("----------------------------------------------\n");
	fmt::print("Instructions:\n");
	fmt::print("Type 'help' to show instructions.\n");
	fmt::print("Type 'exit' to quit.\n");
	fmt::print("----------------------------------------------\n\n");
}