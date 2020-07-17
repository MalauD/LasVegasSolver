#include "PrintCommand.hpp"

void PrintCommand::Execute(std::vector<std::string> args) {
    if(args.empty()){
        throw std::runtime_error("No argument specified to print command");
        return;
    }
    if(args.size() != 1){
        throw std::runtime_error("Expected 1 argument for the print command");
        return;
    }

    if(args[0] == "casinos"){
        auto casinos = GameSandBox::getInstance().GetGameSet().GetCasinos();
        std::for_each(casinos.begin(), casinos.end(),
            [](const Casino& c){
                std::cout << c;
            });
    } else if(args[0] == "dices"){
        auto dices = GameSandBox::getInstance().GetGameSet().GetDiceSets();
        std::for_each(dices.begin(), dices.end(),
            [](const DiceSet& c){
                std::cout << c;
            });
    } else if(args[0] == "order"){
        throw std::runtime_error("Invalid argument: " + args[0]);
    } else{
        throw std::runtime_error("Invalid argument: " + args[0]);
    }
}
