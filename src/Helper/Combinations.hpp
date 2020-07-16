#pragma once
#include <vector>
#include "../Core/DiceSet.hpp"

class Combinations {
    public:
        static std::vector<DiceSet> CombinationsWithRepetitions(int Length, DiceColors color);
};