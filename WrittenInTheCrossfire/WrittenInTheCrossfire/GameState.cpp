#include "GameState.h"
#include "Stats.h"
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
	checkpoint = 1;
	currentStats.mentalWellbeing = 100;
	currentStats.familyRelationship = 100;
	currentStats.patriotism = 100;
}

std::vector<json> GameState::getChatHistory() {
	return chatHistory;
}

void GameState::setChatHistory(std::vector<json> chatHistory) {
	this->chatHistory = chatHistory;
}

int GameState::getCheckpoint() {
	return checkpoint;
}

void GameState::setCheckpoint(int checkpoint) {
	this->checkpoint = checkpoint;
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
		return { true, "Game saved successfully." };
	} else {
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

		return { true, "Save loaded successfully." };
	} else {
		return { false, "No save found." };
	}
}

void GameState::updateCurrentStats(json& sentiments) {
	Stats& newStats = calculateStatChanges(sentiments);

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
}

Stats& GameState::calculateStatChanges(json& sentiments) {
	Stats newStats = { 0, 0, 0 };
	srand(time(0));

	for(auto& item : sentiments.items()) {
		if(item.value() != "NEUTRAL") {
			int statChanges = rand() % 8; // Generates a random value between 0 and 7

			if(item.value() == "EXCELLENT") {
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
				newStats.familyRelationship += statChanges;
			} else if(item.key() == "mentalWellbeing") {
				newStats.mentalWellbeing += statChanges;
			} else if(item.key() == "patriotism") {
				newStats.patriotism += statChanges;
			}
		}
	}

	return newStats;
}

void GameState::updateCheckpoint() {
	checkpoint++;
}