#include "GameModel.h"
#include "Stats.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

GameModel::GameModel() : Model() {
	init();
}

void GameModel::init() {
	checkpoint = 1;
	currentStats.mentalWellbeing = 100;
	currentStats.familyRelationship = 100;
	currentStats.patriotism = 100;
}

std::vector<json> GameModel::getChatHistory() {
	return chatHistory;
}

void GameModel::setChatHistory(std::vector<json> chatHistory) {
	this->chatHistory = chatHistory;
}

int GameModel::getCheckpoint() {
	return checkpoint;
}

void GameModel::setCheckpoint(int checkpoint) {
	this->checkpoint = checkpoint;
}

Stats GameModel::getCurrentStats() {
	return currentStats;
}

void GameModel::setCurrentStats(Stats currentStats) {
	this->currentStats = currentStats;
}

std::tuple<bool, std::string> GameModel::save() {
	json save = *this;
	std::ofstream file = std::ofstream("game.json");

	if(file.is_open()) {
		file << save.dump(4) << std::endl;
		return { true, "Game saved successfully." };
	} else {
		return { false, "Failed to save game." };
	}
}

std::tuple<bool, std::string> GameModel::load() {
	json load;
	std::ifstream file = std::ifstream("game.json");
    
	if(file.is_open()) {
		file >> load;
		auto gameModel = load.template get<GameModel>();

		setChatHistory(gameModel.getChatHistory());
		setCheckpoint(gameModel.getCheckpoint());
		setCurrentStats(gameModel.getCurrentStats());

		return { true, "Save loaded successfully." };
	} else {
		init();
		save();

		return { false, "Failed to load save." };
	}
}