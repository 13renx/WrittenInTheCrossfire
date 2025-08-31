#include "Client.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <dotenv.h>

using json = nlohmann::json;

class Client {
	std::vector<json> history;
	json prompt;
	const char* apiKey;

	public:
		Client() {
			// Set apiKey with API_KEY from .env file
			dotenv::init(".env");
			apiKey = std::getenv("API_KEY");

			try {
				if(apiKey == nullptr) {
					throw std::runtime_error("API_KEY was not found");
				}
			}
			catch(const std::runtime_error& e) {
				std::cout << "Exception: " << e.what() << std::endl;
			} 
		}
};