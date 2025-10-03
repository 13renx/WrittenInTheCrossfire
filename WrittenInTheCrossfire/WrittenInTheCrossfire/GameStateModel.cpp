#include "GameStateModel.h"
#include "Stats.h"
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