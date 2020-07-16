#pragma once
#include "Casino.hpp"
#include "DiceSet.hpp"
#include "PlayingOrder.hpp"

class GameSet {
   private:
       std::vector<Casino> m_Casinos;
       std::vector<DiceSet> m_PlayerDiceSets;
       PlayingOrder m_PlayingOrder;
   public:
       GameSet(std::vector<Casino> Casinos, std::vector<DiceSet> PlayerDiceSets);
       GameSet(std::vector<Casino> Casinos, std::vector<DiceSet> PlayerDiceSets, PlayingOrder playingOrder);
       void AddDiceTo(Dice dice);
       int EvaluateForColor(DiceColors color);
       const std::vector<Casino> GetCasinos();
       Casino& GetCasinoBy(unsigned short Symbol);
       const std::vector<DiceSet> GetDiceSets();
       DiceSet& GetDiceSetBy(DiceColors DiceColor);
       int GetDicesCountBy(DiceColors DiceColor);
       void SetDiceSetOf(DiceColors DiceColor, DiceSet newDiceSet);
       void PlayFor(DiceColors playingFor, unsigned int Symbol);
       PlayingOrder& GetPlayingOrder();
};