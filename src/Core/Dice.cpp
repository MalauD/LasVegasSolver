#include "Dice.hpp"

Dice::Dice(DiceColors Color, unsigned short Val) noexcept : m_Value{Val}, m_Color{ Color }
{
}

const unsigned short Dice::GetValue() const noexcept
{
    return m_Value;
}

const DiceColors Dice::GetColor() const noexcept {
    return m_Color;
}

const std::string Dice::GetColorStr() const noexcept
{
    return AllDiceColorsPrintable.at(static_cast<int>(GetColor()));
}

std::ostream& operator<<(std::ostream& os, const Dice& d) {
    os << d.GetValue() << " " << d.GetColorStr();
    return os;
}

Dice& Dice::operator+=(const int& i) {
    m_Value += i;
    return *this;
}