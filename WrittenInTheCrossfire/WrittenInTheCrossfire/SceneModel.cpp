#include "SceneModel.h"

#include <string>
#include <tuple>
#include <vector>


SceneModel::SceneModel() {
    // 2
	assets.push_back(std::make_tuple(2, "", "The convoy came to a stop before the camp. The men spilled out, half - dazed from the ride, greeted not by welcome but by shouting."));
	assets.push_back(std::make_tuple(2, "", "\"Attention! You\'re soldiers now, not lost sheep. You all are to address me as Sergeant Chaves, and you\'ll be following my orders from now on.\""));
    assets.push_back(std::make_tuple(2, "", "Sergeant Chaves' voice cut through the wind, sharp and unyielding. The air smelled of rust and mud. Somewhere in the distance, the sound of gunfire echoed faintly. The war felt closer than you expected."));
    assets.push_back(std::make_tuple(2, "", "Sergeant Chaves performed a rollcall. One man stammered when called and earned a daunting glare. You kept your eyes forward. Behind you, someone coughed. Another whispered a prayer."));
    assets.push_back(std::make_tuple(2, "", "Everyone arrived at the camp. Rows of iron bunks, the stench of damp uniforms, and the lack of any sanitary equipment."));
    assets.push_back(std::make_tuple(2, "", "You dropped your stuff at your assigned area, surrounded by strangers who all wore the same expression: uncertainty masked as silence."));
    assets.push_back(std::make_tuple(2, "", "One of them laughed under his breath. Another muttered that the place looked more like a prison than a camp."));
    assets.push_back(std::make_tuple(2, "", "You stayed quiet. You didn't join in. You just watched the smoke curl toward the ceiling until the whistle blew for lights out."));
    assets.push_back(std::make_tuple(2, "", "The next day, dawn brought shouting. Everyone gathered to eat their meal."));
    assets.push_back(std::make_tuple(2, "", "\"Finish up quickly. We will be proceeding with drills in a few minutes.\" Sergeant Chaves yelled."));
    assets.push_back(std::make_tuple(2, "", "As soon as the whistle blew, everyone made their way to the training grounds."));
    assets.push_back(std::make_tuple(2, "", "Everyone trained on the mud, performing several drills that tired everyone out. Sergeant Chaves' commands cut through the haze."));
    assets.push_back(std::make_tuple(2, "", "Running, crawling, pushups, situps, rifle handling. All happening with little to no breaks in between."));
    assets.push_back(std::make_tuple(2, "", "\"You'll learn to fight tired, because the enemy won't wait for you to rest!\""));
    assets.push_back(std::make_tuple(2, "", "You stumbled once, earning a boot to the heel and a growl of \"Keep moving.\" By the end of it, your arms shook too much to hold the rifle steady, but you didn't dare to drop it."));
    assets.push_back(std::make_tuple(2, "", "The camp quieted. Occasional murmur from nearby bunks, someone passing around leftover food, another hummed a tune, low and sad."));
    assets.push_back(std::make_tuple(2, "", "This vicious cycle of the campgrounds continues over and over again.This is the new reality for everyone here."));
    assets.push_back(std::make_tuple(2, "", "One fateful evening, papers were being handed out, and it was announced that everyone was given an opportunity to write to their loved ones."));
    assets.push_back(std::make_tuple(2, "", "You sat in your bunk, staring at a blank sheet of paper. Thinking of home, of your Mom you left behind, of how she will feel knowing the circumstances of your situation."));
}

std::vector<std::tuple<int, std::string, std::string>> SceneModel::getCheckpointAssets(int checkpoint) {
    std::vector<std::tuple<int, std::string, std::string>> ret;

    for(const auto& asset : assets) {
        if(std::get<0>(asset) == checkpoint) {
            ret.push_back(asset);
        }
    }

    return ret;
}