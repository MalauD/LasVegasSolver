#pragma once
#include "Dice.hpp"
#include "Ticket.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <experimental/map>

class Casino{
    private:
        unsigned short m_CasinoSymbol;
        std::vector<Ticket> m_Tickets;
        std::vector<Dice> m_Dices;
    public:
        Casino(const std::vector<Ticket> Tickets, unsigned short CasinoSymbol) noexcept;
        void AddDice(const Dice& NewDice) noexcept;
        const unsigned short GetCasinoSymbol() const noexcept;
        std::vector<Dice> GetDicesByColor(const DiceColors& Color) const noexcept;
        std::vector<Dice> GetDices() const noexcept;
        int GetDicesCountByColor(const DiceColors& Color) const;
        int GetSumOfTickets() const noexcept;
        const std::vector<Ticket> GetTickets() const noexcept;
        const std::vector<TicketValues> GetTicketValues() const;
        int GetGainByColor(const DiceColors& color) const noexcept;
        friend std::ostream& operator<<(std::ostream& os, const Casino& casino);
};