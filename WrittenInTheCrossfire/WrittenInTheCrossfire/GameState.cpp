#include "GameState.h"
#include "witc.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

GameState::GameState() {
  checkpoint = 1;
  currentStats.mentalWellbeing = 100;
  currentStats.familyRelationship = 100;
  currentStats.patriotism = 100;
  
  save();
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

witc::stats GameState::getCurrentStats() {
	return currentStats;
}

void GameState::setCurrentStats(witc::stats currentStats) {
	this->currentStats = currentStats;
}

std::tuple<bool, std::string> GameState::save() {
    json save;

    save["chatHistory"] = getChatHistory();
    save["checkpoint"] = getCheckpoint();
    save["currentStats"] = getCurrentStats();

	std::ofstream file("save.json");

	if(file.is_open()) {
		file << save.dump(4) << std::endl;
		return { true, "Game state saved successfully." };
	} else {
		return { false, "Failed to save game state." };
	}
}

std::tuple<bool, std::string> GameState::load() {
    json load;
    std::ifstream file("save.json");
    
    if(file.is_open()) {
      file >> load;
      return { true, "Save loaded successfully." };
    } else {
      return { false, "Failed to load save." };
	  }
}