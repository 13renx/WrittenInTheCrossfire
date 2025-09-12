#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace witc {
    struct stats {
        int mentalWellbeing;
        int familyRelationship;
        int patriotism;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(witc::stats, mentalWellbeing, familyRelationship, patriotism) // Creates to_json() and from_json()
}