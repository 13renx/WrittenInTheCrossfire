#include "SceneModel.h"

#include <string>
#include <tuple>
#include <vector>


SceneModel::SceneModel() {
    // 1
	assets.push_back(std::make_tuple(1, "", "The convoy came to a stop before the camp. The men spilled out, half - dazed from the ride, greeted not by welcome but by shouting."));
	assets.push_back(std::make_tuple(1, "", "\"Attention! You\'re soldiers now, not lost sheep. You all are to address me as Sergeant Chaves, and you\'ll be following my orders from now on.\""));
    assets.push_back(std::make_tuple(1, "", "Sergeant Chaves' voice cut through the wind, sharp and unyielding. The air smelled of rust and mud. Somewhere in the distance, the sound of gunfire echoed faintly. The war felt closer than you expected."));
    assets.push_back(std::make_tuple(1, "", "Sergeant Chaves performed a rollcall. One man stammered when called and earned a daunting glare. You kept your eyes forward. Behind you, someone coughed. Another whispered a prayer."));
    assets.push_back(std::make_tuple(1, "", "Everyone arrived at the camp. Rows of iron bunks, the stench of damp uniforms, and the lack of any sanitary equipment."));
    assets.push_back(std::make_tuple(1, "", "You dropped your stuff at your assigned area, surrounded by strangers who all wore the same expression: uncertainty masked as silence."));
    assets.push_back(std::make_tuple(1, "", "One of them laughed under his breath. Another muttered that the place looked more like a prison than a camp."));
    assets.push_back(std::make_tuple(1, "", "You stayed quiet. You didn't join in. You just watched the smoke curl toward the ceiling until the whistle blew for lights out."));
    assets.push_back(std::make_tuple(1, "", "The next day, dawn brought shouting. Everyone gathered to eat their meal."));
    assets.push_back(std::make_tuple(1, "", "\"Finish up quickly. We will be proceeding with drills in a few minutes.\" Sergeant Chaves yelled."));
    assets.push_back(std::make_tuple(1, "", "As soon as the whistle blew, everyone made their way to the training grounds."));
    assets.push_back(std::make_tuple(1, "", "Everyone trained on the mud, performing several drills that tired everyone out. Sergeant Chaves' commands cut through the haze."));
    assets.push_back(std::make_tuple(1, "", "Running, crawling, pushups, situps, rifle handling. All happening with little to no breaks in between."));
    assets.push_back(std::make_tuple(1, "", "\"You'll learn to fight tired, because the enemy won't wait for you to rest!\""));
    assets.push_back(std::make_tuple(1, "", "You stumbled once, earning a boot to the heel and a growl of \"Keep moving.\" By the end of it, your arms shook too much to hold the rifle steady, but you didn't dare to drop it."));
    assets.push_back(std::make_tuple(1, "", "The camp quieted. Occasional murmur from nearby bunks, someone passing around leftover food, another hummed a tune, low and sad."));
    assets.push_back(std::make_tuple(1, "", "This vicious cycle of the campgrounds continues over and over again.This is the new reality for everyone here."));
    assets.push_back(std::make_tuple(1, "", "One fateful evening, papers were being handed out, and it was announced that everyone was given an opportunity to write to their loved ones."));
    assets.push_back(std::make_tuple(1, "", "You sat in your bunk, staring at a blank sheet of paper. Thinking of home, of your Mom you left behind, of how she will feel knowing the circumstances of your situation."));
    // 2
    assets.push_back(std::make_tuple(2, "", "The days began to blur. The same whistle, the same mud, the same shouts echoing through the camp."));
    assets.push_back(std::make_tuple(2, "", "Breakfast came late. Someone joked about the food tasting worse every day. Another recruit replied, \"You'll eat anything when you're hungry enough.\" A few chuckled."));
    assets.push_back(std::make_tuple(2, "", "The fragments of laughter that sounded out of place in this world of blood, sweat, and tears."));
    assets.push_back(std::make_tuple(2, "", "\"Attention! I want everyone outside by the training grounds in 5 minutes. Latecomers have a punishment.\" Sergeant Chaves yelled."));
    assets.push_back(std::make_tuple(2, "", "No one was late. Sergeant Chaves stood by with his arms crossed as everyone did their drills."));
    assets.push_back(std::make_tuple(2, "", "\"You're not here to enjoy the breeze!\" he barked."));
    assets.push_back(std::make_tuple(2, "", "The dirt kicked up by boots turned to dust in the air, coating every breath."));
    assets.push_back(std::make_tuple(2, "", "One recruit stumbled and nearly collapsed. Chaves yelled for two others to drag him up"));
    assets.push_back(std::make_tuple(2, "", "\"If one man falls, all of you fall!\""));
    assets.push_back(std::make_tuple(2, "", "Your body ached, but the drills didn't stop. You forced yourself to keep moving, jaw clenched, lungs on fire."));
    assets.push_back(std::make_tuple(2, "", "That night, the barracks were quieter than usual. The harsh training that day put a toll on everyone."));
    assets.push_back(std::make_tuple(2, "", "But you overhear the chatters of someone speaking of their background. A few men traded short words about home. Their distant towns, families, and half-remembered meals."));
    assets.push_back(std::make_tuple(2, "", "Hearing those words makes you wonder the same. You think about these thoughts as you fall to sleep."));
    assets.push_back(std::make_tuple(2, "", "The next morning brought new orders. It's time for live-fire exercises."));
    assets.push_back(std::make_tuple(2, "", "Rifles cracked through the fields. The smell of gunpowder filled the air."));
    assets.push_back(std::make_tuple(2, "", "Chaves shouted commands between bursts of noise."));
    assets.push_back(std::make_tuple(2, "", "One man's rifle jammed, another flinched too early. Everyone wavered, but no one stopped."));
    assets.push_back(std::make_tuple(2, "", "The chaos of men shooting rifles. This was the first time you ever shot a gun and it may be the same for many."));
    assets.push_back(std::make_tuple(2, "", "Sergeant Chaves inspected the field, silent for once, only nodding slightly before ordering everyone to clean their rifles."));
    assets.push_back(std::make_tuple(2, "", "Another set of exhausting days of training has passed. You lose count of how long it's been."));
    assets.push_back(std::make_tuple(2, "", "Yet another quiet night and everyone was given a new piece of paper. Another opportunity to write again."));
    // 3
    assets.push_back(std::make_tuple(3, "", "The days pressed on, each one carving away a little more of who you were before you left home."));
    assets.push_back(std::make_tuple(3, "", "Routine had turned into instinct. You woke before the whistle now."));
    assets.push_back(std::make_tuple(3, "", "\"Move, move, move!\" Sergeant Chaves' voice carried across the perimeter."));
    assets.push_back(std::make_tuple(3, "", "You ducked, crawled, and rolled through the mud, feeling the weight of your rifle press into your chest."));
    assets.push_back(std::make_tuple(3, "", "The men no longer groaned out loud, instead they just endured."));
    assets.push_back(std::make_tuple(3, "", "During a drill, you tripped and fell. But someone beside you offered you their hand."));
    assets.push_back(std::make_tuple(3, "", "\"Careful, man. The Sergeant is watching.\""));
    assets.push_back(std::make_tuple(3, "", "You nodded your thanks and he grinned faintly before continuing."));
    assets.push_back(std::make_tuple(3, "", "\"That's enough for now. Enjoy your meal.\""));
    assets.push_back(std::make_tuple(3, "", "You got your portions, started chowing down your food."));
    assets.push_back(std::make_tuple(3, "", "A familiar figure approaches you."));
    assets.push_back(std::make_tuple(3, "", "It was the person that lent you a hand earlier during training."));
    assets.push_back(std::make_tuple(3, "", "\"Hey, mind if I stay here?\""));
    assets.push_back(std::make_tuple(3, "", "The two of you ate together."));
    assets.push_back(std::make_tuple(3, "", "\"The name's Ramos. Not that it matters, but it's nice to see a friendly face out here.\""));
    assets.push_back(std::make_tuple(3, "", "You both chatted about how rough it has been and how much you both miss your homes."));
    assets.push_back(std::make_tuple(3, "", "\"Once we are out of this mess, let's get a few drinks together. How about it?\""));
    assets.push_back(std::make_tuple(3, "", "The optimism and kindness Ramos has filled you with joy as you find yourself making a friend amidst the war."));
    assets.push_back(std::make_tuple(3, "", "\"Attention!\""));
    assets.push_back(std::make_tuple(3, "", "And before you know it, it's back to training."));
    assets.push_back(std::make_tuple(3, "", "Night fell over the camp, the air was thick with the smell of sweat. Sergeant Chaves let everyone rest earlier than usual."));
    assets.push_back(std::make_tuple(3, "", "Ramos visited you and you both chatted."));
    assets.push_back(std::make_tuple(3, "", "\"Quiet down, I'm trying to catch some sleep.\""));
    assets.push_back(std::make_tuple(3, "", "\"Sorry about that.\" Ramos said calmingly."));
    assets.push_back(std::make_tuple(3, "", ""));
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