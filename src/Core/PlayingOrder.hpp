#pragma once
#include "Dice.hpp"
#include <vector>

class PlayingOrder {
    private:
        std::vector<DiceColors> m_PlayingOrder;
        int m_ColorPlayingIndex = 0;
    public:
        PlayingOrder() = default;
        PlayingOrder(std::vector<DiceColors> m_PlayingOrder, DiceColors ColorToPlayNow);
        DiceColors EstimatePlayingIn(int rounds);
        DiceColors Advance(int rounds = 1);
        DiceColors GetPlayingNow();
        std::vector<DiceColors> GetPlayingOrder();
};