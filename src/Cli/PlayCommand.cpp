#include "PlayCommand.hpp"

void PlayCommand::Execute(std::vector<std::string> args) {
    if(args.empty()){
        throw std::runtime_error("No argument specified to play command");
        return;
    }
    if(args.size() != 2){
        throw std::runtime_error("Expected 1 argument for the play command");
        return;
    }

    auto diceChar = args[0].front();
    auto it = std::find(AllDiceColorsCmd.begin(), AllDiceColorsCmd.end(), diceChar);
    if(it == AllDiceColorsCmd.end()) throw std::runtime_error("Invalid dice color: " + diceChar);
    auto color = AllDiceColors[std::distance(AllDiceColorsCmd.begin(), it)];

    auto diceSymbol = std::atoi(args[1].c_str());

    GameSandBox::getInstance().GetGameSet().PlayFor(color, diceSymbol);
    std::cout << "Played move of player " << AllDiceColorsPrintable[std::distance(AllDiceColors.begin(), std::find(AllDiceColors.begin(), AllDiceColors.end(), color))];
    std::cout << " with symbol " << diceSymbol <<"\n";
}
