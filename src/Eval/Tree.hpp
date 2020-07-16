#pragma once
#include <vector>
#include <numeric>
#include "../Core/GameSet.hpp"

class TreeNode {
    private:
        std::vector<TreeNode> m_nodes;
        const int m_id;
        int m_GameSetEval;
    public:
        TreeNode(int id, int gsEval = 0);
        std::vector<TreeNode>& GetChildNodes();
        const int GetId() const noexcept;
        void AddNode(TreeNode node);
        int GetEval();
        void SetEval(int Eval);
        int GetChildNodesCount(int Depth);
};