#pragma once

#include <string>
#include <tuple>
#include <vector>

class SceneModel
{
	private:
		std::vector<std::tuple<int, std::string, std::string>> assets;

	public:
		SceneModel();

		std::vector<std::tuple<int, std::string, std::string>> getCheckpointAssets(int checkpoint);
};