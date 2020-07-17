#pragma once
#include <array>
#include <iostream>
#include <string>

enum class DiceColors {
    undefined,
    Red,
    Blue,
    Yellow,
    Black,
    Green
};

static const std::array<DiceColors, 6> AllDiceColors = {
    DiceColors::undefined,
    DiceColors::Red,
    DiceColors::Blue,
    DiceColors::Yellow,
    DiceColors::Black,
    DiceColors::Green
};

static const std::array<std::string, 6> AllDiceColorsPrintable = {
    "N/A",
    "Red",
    "Blue",
    "Yellow",
    "Black",
    "Green"
};

static const std::array<char, 6> AllDiceColorsCmd = {
    '0',
    'R',
    'B',
    'Y',
    'N',
    'G'
};

class Dice {
    private:
        unsigned short m_Value = 0;
        DiceColors m_Color = DiceColors::undefined;
    public:
        Dice(DiceColors Color, unsigned short Val) noexcept;
        const unsigned short GetValue() const noexcept;
        const DiceColors GetColor() const noexcept;
        const std::string GetColorStr() const noexcept;
        friend std::ostream& operator<<(std::ostream& os, const Dice& d);
        operator int() const {return m_Value; };
        Dice& operator+=(const int& i);
};