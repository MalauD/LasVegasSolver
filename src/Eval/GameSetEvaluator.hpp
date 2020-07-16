#pragma once
#include "../Core/GameSet.hpp"
#include "Tree.hpp"
#include "../Helper/Combinations.hpp"

class GameSetEvaluator {
    public:
        std::map<int, int> EvalGameSetFor(GameSet Gs, DiceColors For, int Depth = 2);
        TreeNode GetNodeFor(GameSet Gs, DiceColors dc, int MaxDepth = 2, int Depth = 0);
        long long NodesCount = 0;
};