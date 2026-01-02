#include "Utils.h"
#include <string>
#include "spdlog/spdlog.h"

void Utils::Log::info(std::string text) {
	#ifdef _DEBUG
		spdlog::info(text);
	#endif
}

void Utils::Log::warn(std::string text) {
	#ifdef _DEBUG
		spdlog::warn(text);
	#endif
}

void Utils::Log::error(std::string text) {
	#ifdef _DEBUG
		spdlog::error(text);
	#endif
}

void Utils::Log::critical(std::string text) {
	#ifdef _DEBUG
		spdlog::critical(text);
	#endif
}