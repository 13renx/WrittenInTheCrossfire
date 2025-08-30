#include "Client.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <dotenv.h>

using json = nlohmann::json;

class Client {
	std::vector<json> history;
	json prompt;
	const std::string apiKey;

	public:
		Client() {

		}
};