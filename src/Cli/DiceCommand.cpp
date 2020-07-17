#include "DiceCommand.hpp"


void DiceCommand::Execute(std::vector<std::string> args) {
    if(args.empty()){
        throw std::runtime_error("No argument specified to dice command");
        return;
    }
    if(args.size() != 2){
        throw std::runtime_error("Expected 2 arguments for the dice command.");
        return;
    }

    auto diceChar = args[0].front();
    auto it = std::find(AllDiceColorsCmd.begin(), AllDiceColorsCmd.end(), diceChar);
    if(it == AllDiceColorsCmd.end()) throw std::runtime_error("Invalid dice color: " + diceChar);
    auto color = AllDiceColors[std::distance(AllDiceColorsCmd.begin(), it)];
    std::vector<Dice> dices;
    for(const char& c : args[1]){
        std::string s(1, c);//! ugly
        auto diceNumber = std::atoi(s.c_str());
        if(diceNumber > 6 || diceNumber < 1) throw std::runtime_error("Dice should have a value between 1 and 6");
        dices.push_back(Dice(color, diceNumber));
    }
    auto& ds = GameSandBox::getInstance().GetGameSet().GetDiceSetBy(color);
    ds.SetTo(dices);
    std::cout << "Dices sets to: \n";
    std::cout << ds;
}
