#include "Tree.hpp"

TreeNode::TreeNode(int id, int gsEval) : m_id{id}, m_GameSetEval{gsEval} {
}

std::vector<TreeNode>& TreeNode::GetChildNodes() {
    return m_nodes;
}

const int TreeNode::GetId() const noexcept {
    return m_id;
}

void TreeNode::AddNode(TreeNode newChild) {
    m_nodes.push_back(newChild);
}

int TreeNode::GetEval() {
    int endEval = m_GameSetEval;
    if (m_nodes.empty()) {
        return endEval;
    }
    return std::accumulate(m_nodes.begin(), m_nodes.end(), 0,
		[](int prev, TreeNode Tn) {
			return prev + Tn.GetEval();
		});
}

void TreeNode::SetEval(int Eval)
{
    m_GameSetEval = Eval;
}

int TreeNode::GetChildNodesCount(int Depth)
{
    if (m_id >= Depth) return m_nodes.size();
    return std::accumulate(m_nodes.begin(), m_nodes.end(), 0,
        [Depth](int prev, TreeNode Tn) {
            return prev + Tn.GetChildNodesCount(Depth);
        });
}
