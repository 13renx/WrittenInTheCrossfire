#include "Client.h"
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Client {
	json history;
	json prompt;
	const std::string apiKey;

};