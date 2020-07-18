#include "DiceSet.hpp"

DiceSet::DiceSet(std::vector<Dice> Dices) : m_Dices{Dices}
{

}

DiceSet::DiceSet(int DiceCount, DiceColors Dc, unsigned short Vals)
{
    m_Dices.resize(DiceCount, Dice(Dc, Vals));
}

std::vector<Dice> DiceSet::GetAndRemove(unsigned short ValueToSortOut){
   std::vector<Dice> dicesToRemove = Get(ValueToSortOut);

   m_Dices.erase(std::remove_if(m_Dices.begin(), m_Dices.end(), [&ValueToSortOut](const Dice& d){
       return d.GetValue() == ValueToSortOut;
   }), m_Dices.end());
   
   return dicesToRemove;
}

std::vector<Dice> DiceSet::Get(unsigned short ValueToSortOut){
   std::vector<Dice> dicesToGet;

   const auto HasTheSameVal = [&ValueToSortOut](const Dice& d){
       return d.GetValue() == ValueToSortOut;
   };

   std::copy_if(m_Dices.begin(), m_Dices.end(), std::back_inserter(dicesToGet),HasTheSameVal);
   
   return dicesToGet;
}

std::vector<Dice> DiceSet::GetAll()
{
    return m_Dices;
}

DiceColors DiceSet::GetColorOfFirst() const {
    if(m_Dices.empty()) return DiceColors::undefined;
    return m_Dices.front().GetColor();
}

unsigned short DiceSet::GetValueOfFirst() const {
    if(m_Dices.empty()) return 0;
    return m_Dices.front().GetValue();
}

bool DiceSet::HasSymbol(unsigned short Symbol)
{
    return std::find_if(m_Dices.begin(), m_Dices.end(), [&Symbol](const Dice& d){
        return d.GetValue() == Symbol;
        }) != m_Dices.end();
}

const std::vector<int> DiceSet::GetPossibleOutcomes(DiceSet diceSet) {
    std::vector<int> PossibleSymbolsToPlay{1,2,3,4,5,6};
    std::vector<int> Outcomes;
    Outcomes.reserve(6);
    std::for_each(PossibleSymbolsToPlay.begin(), PossibleSymbolsToPlay.end(), [&diceSet, &Outcomes](int Symbol) {
        if(diceSet.HasSymbol(Symbol)) Outcomes.emplace_back(Symbol);
    });
    return Outcomes;
}

std::ostream& operator<<(std::ostream& os, const DiceSet& Ds) {
   os << "DiceSet: \n";
   for (const Dice& d : Ds.m_Dices) {
       os << "   * " << d << "\n";
   };
   return os;
}

void DiceSet::SetTo(std::vector<Dice> Dices)
{
    m_Dices = Dices;
}

Dice& DiceSet::operator[](int index) {
    return m_Dices[index];
}

int DiceSet::GetDicesCount() {
    return m_Dices.size();
}