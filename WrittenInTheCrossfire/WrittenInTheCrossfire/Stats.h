#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Stats {
    int mentalWellbeing;
    int familyRelationship;
    int patriotism;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Stats, mentalWellbeing, familyRelationship, patriotism) // Creates to_json() and from_json() for Stats