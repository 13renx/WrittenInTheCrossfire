#include "SceneModel.h"

#include <string>
#include <tuple>
#include <vector>


SceneModel::SceneModel() {
	assets.push_back(std::make_tuple(2, "", "The convoy came to a stop before the camp. The men spilled out, half - dazed from the ride, greeted not by welcome but by shouting."));
	assets.push_back(std::make_tuple(2, "", "\"Attention! You\'re soldiers now, not lost sheep. You all are to address me as Sergeant Chaves, and you\'ll be following my orders from now on.\""));
}

std::vector<std::tuple<int, std::string, std::string>>& SceneModel::getCheckpointAssets(int checkpoint) {
    std::vector<std::tuple<int, std::string, std::string>> ret;

    for(const auto& asset : assets) {
        if(std::get<0>(asset) == checkpoint) {
            ret.push_back(asset);
        }
    }

    return ret;
}