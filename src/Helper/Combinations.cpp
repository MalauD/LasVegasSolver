#include "Combinations.hpp"

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

std::vector<DiceSet> Combinations::CombinationsWithRepetitions(int Length, DiceColors color) {
        const auto VecLength = factorial(6 + Length - 1) / (factorial(Length) * factorial(6 - 1));    
        std::vector<DiceSet> res;
        res.reserve(VecLength);
        std::vector<Dice> tempDices(Length + 1, Dice(color, 1));
        DiceSet v = DiceSet(Length + 1, color, 1);
        while (true){ 
                for (int i = 0; i < Length; ++i){
                        if (tempDices[i] > 6){
                            tempDices[i + 1] += 1;
                                for (int k = i; k >= 0; --k){ 
                                    tempDices[k] = tempDices[i + 1];
                                } 
                        } 
                } 
 
                if (tempDices[Length] > 1)
                        break; 
                
                std::vector<Dice> DicesToPush;
                std::copy_n(tempDices.begin(), Length, std::back_inserter(DicesToPush));
                res.push_back(DiceSet(DicesToPush));
                tempDices[0] += 1;
        }
        return res;
}