#include "PlayingOrder.hpp"

PlayingOrder::PlayingOrder(std::vector<DiceColors> PlayingOrder, DiceColors ColorToPlayNow)
    : m_PlayingOrder{PlayingOrder} 
{
    m_ColorPlayingIndex = std::find_if(m_PlayingOrder.begin(), m_PlayingOrder.end(),
        [&ColorToPlayNow](const DiceColors& dc ) {
            return ColorToPlayNow == dc;
        }) - m_PlayingOrder.begin();
}

DiceColors PlayingOrder::EstimatePlayingIn(int rounds) {
    return *std::next(m_PlayingOrder.begin(), (m_ColorPlayingIndex + rounds) % m_PlayingOrder.size());
}

DiceColors PlayingOrder::Advance(int rounds) {
    const auto pNext = std::next(m_PlayingOrder.begin(), (m_ColorPlayingIndex + rounds) % m_PlayingOrder.size());
    m_ColorPlayingIndex = pNext - m_PlayingOrder.begin();
    return *pNext;
}

DiceColors PlayingOrder::GetPlayingNow() {
    return m_PlayingOrder[m_ColorPlayingIndex];
}