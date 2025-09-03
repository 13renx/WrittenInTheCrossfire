#define _CRT_SECURE_NO_WARNINGS

#include "Client.h"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <dotenv.h>

using json = nlohmann::json;

Client::Client() {

}

void Client::setApiKey(const std::string& key) {
	apiKey = key;

}