#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <dotenv.h>
#include <cpr/cpr.h>

void printInstructions();

int main()
{
	dotenv::init(".env");
	const std::string apiKey = std::getenv("API_KEY");
	std::string userInput;
	std::string data;

	std::cout << "Terminal AI Chatbot using C++ and Gemini API";
	printInstructions();

	do {
		std::cout << "> ";
		std::getline(std::cin, userInput);

		if (userInput == "help") {
			printInstructions();
		}
		else if (userInput == "exit") {
			std::cout << "Thanks for using the chatbot!" << "\n";
			break;
		}
		else if (userInput != "") {
			data = R"({ "contents": [{ "parts": [ { "text": ")" + userInput + R"(" }] }] })";

			cpr::Response res = cpr::Post(cpr::Url{ "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent" },
				cpr::Parameters{ { "key", apiKey } },
				cpr::Header{ { "Content-Type", "application/json" } },
				cpr::Body{ data });

			std::cout << res.text << "\n";
		}
	} while (true);

	return 0;
}

void printInstructions() {
	std::cout << "\n" << "----------------------------------------------" << "\n";
	std::cout << "Instructions:" << "\n";
	std::cout << "Type 'help' to show instructions." << "\n";
	std::cout << "Type 'exit' to quit." << "\n";
	std::cout << "----------------------------------------------" << "\n\n";
}