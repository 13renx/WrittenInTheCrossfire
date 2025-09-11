#include "GameState.h"
#include "Stats.h"
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

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

stats GameState::getCurrentStats() {
	return currentStats;
}

void GameState::setCurrentStats(stats currentStats) {
	this->currentStats = currentStats;
}

void GameState::save() {
    json save;
    save["chatHistory"] = getCurrentStats();
    save["checkpoint"] = getCheckpoint();
    save["currentStats"] = getCurrentStats();
}

void GameState::load() {
    
}