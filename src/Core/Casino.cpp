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
    auto sortedTickets(m_Tickets);
    std::sort(sortedTickets.rbegin(),sortedTickets.rend());

    std::map<DiceColors, int> diceCountPerColor;

    std::for_each(AllDiceColors.begin(), AllDiceColors.end(),
        [this, &diceCountPerColor](const DiceColors& Dc) {  //? Shouldn't capture this here
            if(Dc != DiceColors::undefined) {
                diceCountPerColor.insert({Dc, GetDicesCountByColor(Dc)});
            }
        });

    int DicesCountOfRequest = diceCountPerColor[color];
    diceCountPerColor.erase(color);

    for(const DiceColors& diceColor : AllDiceColors){
        if(sortedTickets.empty()) return 0;
        auto maxDiceCount = std::max_element(diceCountPerColor.begin(), diceCountPerColor.end(),
            [](const auto& p1, const auto& p2){
                return p1.second < p2.second;
            });

        if(DicesCountOfRequest > maxDiceCount->second) return sortedTickets.front().GetValueInt();
        if(DicesCountOfRequest == maxDiceCount->second) return 0;
        
        std::map<DiceColors, int> dicesWithSameCount;
        std::copy_if(diceCountPerColor.begin(), diceCountPerColor.end(),
                std::inserter(dicesWithSameCount, dicesWithSameCount.end()),
                [&maxDiceCount](const auto& p){
                    return p.second == maxDiceCount->second;
                });

        if (dicesWithSameCount.size() <= 1) {
            diceCountPerColor.erase(maxDiceCount->first);
            sortedTickets.erase(sortedTickets.begin());
        }
        else {
            std::for_each(dicesWithSameCount.begin(), dicesWithSameCount.end(),
                [&diceCountPerColor](const auto& p) {
                    diceCountPerColor.erase(p.first);
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
        const auto g = casino.GetGainByColor(c);
        if (c == DiceColors::undefined || g == 0) continue;
        os << "   * " << AllDiceColorsPrintable.at(static_cast<int>(c)) << " ";
        os << g << "\n";
    };
    os << "\n";
    return os;
}