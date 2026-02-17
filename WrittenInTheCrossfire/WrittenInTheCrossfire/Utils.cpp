#include "Utils.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <fmt/core.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

std::string Utils::Log::fileName = "";
spdlog::logger Utils::Log::logger = spdlog::logger("");

void Utils::Log::init() {
    if(fileName == "") {
        time_t now = time(NULL);
        char str[26] = {};
        ctime_s(str, 26, &now);
        fileName = str;
        std::replace(fileName.begin(), fileName.end(), ':', '-');
        fileName.pop_back(); // Remove newline
        fileName = fmt::format("./Logs/{}.txt", fileName);

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fileName, true);
        logger = spdlog::logger("multi_sink", { console_sink, file_sink });
    }
}

void Utils::Log::debugInfo(std::string text) {
    #ifdef _DEBUG
        logger.info(text);
    #endif
}

void Utils::Log::info(std::string text) {
    logger.info(text);
}

void Utils::Log::warn(std::string text) {
    logger.warn(text);
}

void Utils::Log::error(std::string text) {
    logger.error(text);
}

void Utils::Log::critical(std::string text) {
    logger.critical(text);
}