#include "StartCommand.hpp"

/** Example: start 3 BGY 30,80/60/50/30,20/90
 * 
 */
void StartCommand::Execute(std::vector<std::string> args) {
    if(args.empty()){
        throw std::runtime_error("No argument specified to start command");
        return;
    }
    if(args.size() != 3){
        throw std::runtime_error("Expected 3 arguments for the start command. Example start 3 BGY 30,80/60/50/30,20/90");
        return;
    }

    auto playerCount = std::atoi(args[0].c_str());
    auto& gs = GameSandBox::getInstance().GetGameSet();

    std::vector<DiceSet> diceSets;
    std::vector<DiceColors> order;
    for(const char& c: args[1]) {   
        auto it = std::find(AllDiceColorsCmd.begin(), AllDiceColorsCmd.end(),c);
        if(it == AllDiceColorsCmd.end()) throw std::runtime_error("Invalid dice color: " + c);
        auto color = AllDiceColors[std::distance(AllDiceColorsCmd.begin(), it)];
        diceSets.push_back(DiceSet(8,color, 1));
        order.push_back(color);
    }

    auto playingOrder = PlayingOrder(order, order.front());

    auto splittedTicketsArg = StringHelper::split(args[2], '/');
    if(splittedTicketsArg.size() != 5) throw std::runtime_error("Invalid tickets count, need 5");
    int cSymbol = 1;
    std::vector<Casino> casinos;
    for(const std::string& casTickets: splittedTicketsArg){
        std::vector<Ticket> tickets;
        auto ticketsIn = StringHelper::split(casTickets, ',');
        for(const std::string& t: ticketsIn) {
            auto parsedTicket = std::atoi(t.c_str());
            tickets.push_back(Ticket(static_cast<TicketValues>(parsedTicket)));
        }
        casinos.push_back(Casino(tickets,cSymbol));

        cSymbol++;
    }
    gs.ResetTo(casinos, diceSets, playingOrder);
}
