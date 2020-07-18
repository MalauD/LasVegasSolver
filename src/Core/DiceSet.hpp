#pragma once
#include "Dice.hpp"
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

class DiceSet {
   private:
       std::vector<Dice> m_Dices;
   public:
       DiceSet(std::vector<Dice> Dices);
       DiceSet(int DiceCount, DiceColors dicesColor, unsigned short dicesVal);
       std::vector<Dice> GetAndRemove(unsigned short ValueToSortOut);
       std::vector<Dice> Get(unsigned short ValueToSortOut);
       std::vector<Dice> GetAll();
       DiceColors GetColorOfFirst() const;
       unsigned short GetValueOfFirst() const;
       bool HasSymbol(unsigned short Symbol);
       static const std::vector<int> GetPossibleOutcomes(DiceSet diceSet);
       friend std::ostream& operator<<(std::ostream& os, const DiceSet& Ds);
       void SetTo(std::vector<Dice> Dices);
       Dice& operator[](int index);
       int GetDicesCount();
};