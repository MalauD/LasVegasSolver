#include "Casino.hpp"

Casino::Casino(const std::vector<Ticket> Tickets, unsigned short CasinoSymbol) noexcept : m_Tickets{Tickets}, m_CasinoSymbol{ CasinoSymbol }
{
}

void Casino::AddDice(const Dice& NewDice) noexcept
{
    if(NewDice.GetValue() == GetCasinoSymbol()) {
        m_Dices.push_back(NewDice);
    }
    else {
        throw std::runtime_error("Invalid dice number");
    }
}

const unsigned short Casino::GetCasinoSymbol() const noexcept
{
    return m_CasinoSymbol;
}

std::vector<Dice> Casino::GetDicesByColor(const DiceColors& Color) const noexcept
{
    std::vector<Dice> filteredDices;
    auto s = std::copy_if(m_Dices.begin(), m_Dices.end(), std::back_inserter(filteredDices), [&Color](Dice d){
        return d.GetColor() == Color;
    });

    return filteredDices;
}

int Casino::GetDicesCountByColor(const DiceColors& Color) const
{
    return std::count_if(m_Dices.begin(), m_Dices.end(), [&Color](const Dice& d) {
            return d.GetColor() == Color;
        });
}

int Casino::GetSumOfTickets() const noexcept
{
     return std::accumulate(m_Tickets.begin(), m_Tickets.end(), 0, 
        [](int prev, const Ticket& t){
            return static_cast<int>(t.GetValue()) + prev;
        });
}

const std::vector<Ticket> Casino::GetTickets() const noexcept
{
    return m_Tickets;
}

const std::vector<TicketValues> Casino::GetTicketValues() const
{
    std::vector<TicketValues> ticketValues;
    std::transform(m_Tickets.begin(), m_Tickets.end(),
        std::back_inserter(ticketValues),
        [](const Ticket& e) {
            return e.GetValue();
        });
    return ticketValues;
}

int Casino::GetGainByColor(const DiceColors& color) const noexcept
{
    if (m_Tickets.empty() || m_Dices.empty()) return 0;
    auto sortedTickets(m_Tickets);
    std::sort(sortedTickets.rbegin(),sortedTickets.rend());

    std::map<DiceColors, int> diceCountPerColor;
    
    for (auto v : m_Dices)
        ++diceCountPerColor[v.GetColor()];

    

    int DicesCountOfRequest = diceCountPerColor[color];
    if (DicesCountOfRequest == 0) return 0;
    diceCountPerColor.erase(color);

    for(const DiceColors& diceColor : AllDiceColors){
        if(sortedTickets.empty()) return 0;
        auto maxDiceCount = std::max_element(diceCountPerColor.begin(), diceCountPerColor.end(),
            [](const auto& p1, const auto& p2){
                return p1.second < p2.second;
            });

        if(DicesCountOfRequest > maxDiceCount->second) return sortedTickets.front().GetValueInt();
        if(DicesCountOfRequest == maxDiceCount->second) return 0;
        
        //std::map<DiceColors, int> dicesWithSameCount;
        auto dicesWithSameCountCount = std::count_if(diceCountPerColor.begin(), diceCountPerColor.end(),
                [&maxDiceCount](const auto& p){
                    return p.second == maxDiceCount->second;
                });

        if (dicesWithSameCountCount <= 1) {
            diceCountPerColor.erase(maxDiceCount->first);
            sortedTickets.erase(sortedTickets.begin());
        }
        else {
            std::experimental::erase_if(diceCountPerColor,
                [&maxDiceCount](const auto& p) {
                    return p.second == maxDiceCount->second;
                });
        }
    }
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Casino& casino){
    os << "\nCasino (Symbol: " << casino.GetCasinoSymbol() << " )\n";
    os << "Details: \n";
    os << " - Tickets (Total: " << casino.GetSumOfTickets() << "): \n";
    for(const Ticket& t : casino.GetTickets()){
        os << "   * " <<  t.GetValueInt() << "\n";
    }
    os << " - Dices: \n";
    for (const Dice& d : casino.m_Dices) {
        os << "   * " << d << "\n";
    }
    os << " - Current gains by color: \n";
    for (const DiceColors& c : AllDiceColors) {
        if (c == DiceColors::undefined) continue;
        const auto g = casino.GetGainByColor(c);
        if (g == 0) continue;
        os << "   * " << AllDiceColorsPrintable.at(static_cast<int>(c)) << " ";
        os << g << "\n";
    };
    os << "\n";
    return os;
}