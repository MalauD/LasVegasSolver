#include "GameSetWriter.hpp"

std::string GameSetWriter::GetGameSetRepresentation(GameSet gs) {
    std::ostringstream gameSetRep;
    auto Casinos = gs.GetCasinos();
    std::sort(Casinos.begin(), Casinos.end(), [](Casino a, Casino b) {
        return a.GetCasinoSymbol() < b.GetCasinoSymbol();
    });

    for(const Casino& c: Casinos) {
        auto casinoDices = c.GetDices();

        for(const Dice& d: casinoDices) {
            auto it = std::find(AllDiceColors.begin(), AllDiceColors.end(), d.GetColor());
            auto colorStr = AllDiceColorsCmd[std::distance(AllDiceColors.begin(), it)];
            gameSetRep << colorStr;
        }
        gameSetRep << '|';
        
        auto casinoTickets = c.GetTickets();

        for(const Ticket& t: casinoTickets) {
            gameSetRep << t.GetValueInt();
            gameSetRep << ',';
        }
        gameSetRep << '/';
    }

    gameSetRep << ' ';
    auto playingOrder = gs.GetPlayingOrder();
    auto order = playingOrder.GetPlayingOrder();
    for (const DiceColors& dc : order) {
        auto it = std::find(AllDiceColors.begin(), AllDiceColors.end(), dc);
        auto colorStr = AllDiceColorsCmd[std::distance(AllDiceColors.begin(), it)];
        gameSetRep << colorStr;
    }

    gameSetRep << ' ';

    auto it = std::find(AllDiceColors.begin(), AllDiceColors.end(), playingOrder.GetPlayingNow());
    auto colorStr = AllDiceColorsCmd[std::distance(AllDiceColors.begin(), it)];
    gameSetRep << colorStr;

    gameSetRep << ' ';

    for (const DiceColors& dc : order) {
        auto ds = gs.GetDiceSetBy(dc);;
        auto dices = ds.GetAll();

        for (const Dice& d : dices) {
            gameSetRep << d.GetValue();
        }
        gameSetRep << '/';
    }


    return gameSetRep.str();
}

GameSet GameSetWriter::GetGameSetFromStr(std::string input)
{
    auto repParts = StringHelper::split(input, ' ');

    auto CasinosPart = StringHelper::split(repParts[0], '/');

    std::vector<Casino> casinos;

    int Symbol = 1;
    for (const auto& CasinoStr : CasinosPart) {
        if (!CasinoStr.empty()) {

            auto TicketDicesPart = StringHelper::split(CasinoStr, '|');

            

            std::vector<Ticket> tickets;
            auto ticketsIn = StringHelper::split(TicketDicesPart[1], ',');
            for (const std::string& t : ticketsIn) {
                auto parsedTicket = std::atoi(t.c_str());
                tickets.push_back(Ticket(static_cast<TicketValues>(parsedTicket)));
            }

            auto c = Casino(tickets, Symbol);

            auto Dicespart = TicketDicesPart[0];
            for (const auto& dice : Dicespart) {
                auto it = std::find(AllDiceColorsCmd.begin(), AllDiceColorsCmd.end(), dice);
                if (it == AllDiceColorsCmd.end()) throw std::runtime_error("Invalid dice color: " + dice);
                auto color = AllDiceColors[std::distance(AllDiceColorsCmd.begin(), it)];

                c.AddDice(Dice(color, Symbol));
            }
            casinos.push_back(c);
        }
        Symbol++;
    }

    std::vector<DiceColors> order;
    for (const char& c : repParts[1]) {
        //TODO Place this in a factory 
        auto it = std::find(AllDiceColorsCmd.begin(), AllDiceColorsCmd.end(), c);
        if (it == AllDiceColorsCmd.end()) throw std::runtime_error("Invalid dice color: " + c);
        auto color = AllDiceColors[std::distance(AllDiceColorsCmd.begin(), it)];
        order.push_back(color);
    }

    auto it = std::find(AllDiceColorsCmd.begin(), AllDiceColorsCmd.end(), repParts[2].front());
    if (it == AllDiceColorsCmd.end()) throw std::runtime_error("Invalid dice color: " + repParts[2].front());
    auto color = AllDiceColors[std::distance(AllDiceColorsCmd.begin(), it)];

    auto playingOrder = PlayingOrder(order, color);

    auto dsStrs = StringHelper::split(repParts[3], '/');

    std::vector<DiceSet> dsList;

    for (int i = 0; i < dsStrs.size(); i++) {
        std::vector<Dice> dices;

        auto currentDice = dsStrs[i];
        for (const char& c : currentDice) {
            std::string s(1, c);//! ugly
            auto diceNumber = std::atoi(s.c_str());
            dices.push_back(Dice(order[i], diceNumber));
        }
        dsList.push_back(DiceSet(dices));
    }

    return GameSet(casinos, dsList, playingOrder);
}
