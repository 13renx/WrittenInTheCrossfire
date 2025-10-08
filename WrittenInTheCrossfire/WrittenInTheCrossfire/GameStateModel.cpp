#include "GameStateModel.h"
#include "Stats.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

GameStateModel::GameStateModel() : Model() {
	init();
}

void GameStateModel::init() {
	checkpoint = 1;
	currentStats.mentalWellbeing = 100;
	currentStats.familyRelationship = 100;
	currentStats.patriotism = 100;
}

std::vector<json> GameStateModel::getChatHistory() {
	return chatHistory;
}

void GameStateModel::setChatHistory(std::vector<json> chatHistory) {
	this->chatHistory = chatHistory;
}

int GameStateModel::getCheckpoint() {
	return checkpoint;
}

void GameStateModel::setCheckpoint(int checkpoint) {
	this->checkpoint = checkpoint;
}

Stats GameStateModel::getCurrentStats() {
	return currentStats;
}

void GameStateModel::setCurrentStats(Stats currentStats) {
	this->currentStats = currentStats;
}

std::tuple<bool, std::string> GameStateModel::save() {
	json save = *this;
	std::ofstream file = std::ofstream("game.json");

	if(file.is_open()) {
		file << save.dump(4) << std::endl;
		return { true, "Game saved successfully." };
	} else {
		return { false, "Failed to save game." };
	}
}

std::tuple<bool, std::string> GameStateModel::load() {
	json load;
	std::ifstream file = std::ifstream("game.json");
    
	if(file.is_open()) {
		file >> load;
		auto gameStateModel = load.template get<GameStateModel>();

		setChatHistory(gameStateModel.getChatHistory());
		setCheckpoint(gameStateModel.getCheckpoint());
		setCurrentStats(gameStateModel.getCurrentStats());

		return { true, "Save loaded successfully." };
	} else {
		init();
		save();

		return { false, "Failed to load save." };
	}
}

Stats GameStateModel::calculateNewStats(json sentiments) {
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

	if(newStats.familyRelationship > 100) {
		newStats.familyRelationship = 100;
	}
	if(newStats.mentalWellbeing > 100) {
		newStats.mentalWellbeing = 100;
	}
	if(newStats.patriotism > 100) {
		newStats.patriotism = 100;
	}

	return newStats;
}