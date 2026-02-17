#include "GameState.h"
#include "Stats.h"
#include "Utils.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

GameState::GameState() : Model() {
	init();
}

void GameState::init() {
	checkpoint = 0;
	currentStats.mentalWellbeing = 100;
	currentStats.familyRelationship = 100;
	currentStats.patriotism = 100;
	chatHistory = std::vector<json>();
}

std::vector<json> GameState::getChatHistory() {
	return chatHistory;
}

void GameState::setChatHistory(std::vector<json> chatHistory) {
	this->chatHistory = chatHistory;
	Utils::Log::debugInfo("chatHistory updated");

	json jsonArray = json::array();
	for(const auto& item : chatHistory) {
		jsonArray.push_back(item);
	}
	Utils::Log::debugInfo(fmt::format("chatHistory = {}", jsonArray.dump()));
}

int GameState::getCheckpoint() {
	return checkpoint;
}

void GameState::setCheckpoint(int checkpoint) {
	this->checkpoint = checkpoint;
	Utils::Log::debugInfo("checkpoint updated");
	Utils::Log::debugInfo(fmt::format("checkpoint = {}", this->checkpoint));
}

Stats& GameState::getCurrentStats() {
	return currentStats;
}

void GameState::setCurrentStats(Stats& currentStats) {
	this->currentStats = currentStats;
}

std::tuple<bool, std::string> GameState::save() {
	json save = *this;
	std::ofstream file = std::ofstream("game.json");

	if(file.is_open()) {
		file << save.dump(4) << std::endl;

		Utils::Log::info("Game saved");
		return { true, "Game saved successfully." };
	} else {
		Utils::Log::error("Game save failed");
		return { false, "Failed to save game." };
	}
}

std::tuple<bool, std::string> GameState::load() {
	json load;
	std::ifstream file = std::ifstream("game.json");
    
	if(file.is_open()) {
		file >> load;
		auto gameState = load.template get<GameState>();

		setChatHistory(gameState.getChatHistory());
		setCheckpoint(gameState.getCheckpoint());
		setCurrentStats(gameState.getCurrentStats());

		Utils::Log::info("Game loaded");
		return { true, "Save loaded successfully." };
	} else {
		Utils::Log::error("Game load failed");
		return { false, "No save found." };
	}
}

void GameState::updateCurrentStats(json& sentiments) {
	Stats newStats = calculateStatChanges(sentiments);

	currentStats.familyRelationship += newStats.familyRelationship;
	currentStats.mentalWellbeing += newStats.mentalWellbeing;
	currentStats.patriotism += newStats.patriotism;

	if(currentStats.familyRelationship > 100) {
		currentStats.familyRelationship = 100;
	}
	if(currentStats.mentalWellbeing > 100) {
		currentStats.mentalWellbeing = 100;
	}
	if(currentStats.patriotism > 100) {
		currentStats.patriotism = 100;
	}

	Utils::Log::debugInfo("currentStats updated");
	Utils::Log::debugInfo(fmt::format("currentStats.mentalWellbeing = {}\ncurrentStats.familyRelationship = {}\ncurrentStats.patriotism = {}", currentStats.mentalWellbeing, currentStats.familyRelationship, currentStats.patriotism));
}

Stats GameState::calculateStatChanges(json& sentiments) {
	Stats newStats = { 0, 0, 0 };
	srand(time(0));

	for(auto& item : sentiments.items()) {
		int statChanges = rand() % 7 + 1; // Generates a random value between 1 and 7
			
		if(item.value() == "NEUTRAL") {
			statChanges *= 0;
		} else if(item.value() == "EXCELLENT") {
			statChanges += 14;
		} else if(item.value() == "GOOD") {
			statChanges += 7;
		} else if(item.value() == "POOR") {
			statChanges *= -1;
		} else if(item.value() == "BAD") {
			statChanges = statChanges * -1 - 7;
		} else if(item.value() == "TERRIBLE") {
			statChanges = statChanges * -1 - 14;
		}

		if(item.key() == "familyRelationship") {
			newStats.familyRelationship = statChanges;
		} else if(item.key() == "mentalWellbeing") {
			newStats.mentalWellbeing = statChanges;
		} else if(item.key() == "patriotism") {
			newStats.patriotism = statChanges;
		}
	}

	return newStats;
}

void GameState::incrementCheckpoint() {
	checkpoint++;
	Utils::Log::debugInfo("checkpoint updated");
	Utils::Log::debugInfo(fmt::format("checkpoint = {}", checkpoint));
}