#include <iostream>

#include "Cli.hpp"

void Cli::Start() {
    std::string input;
    do {
        std::string commandLine;
        std::cout << "LVS> ";
        std::getline(std::cin, commandLine);

        try {
            auto commandArgs = CommandSplitter(commandLine);
            CommandFactory::GetCommandFromStr(commandArgs.first)->Execute(commandArgs.second);
        }
        catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
        
    } while(true);
}



std::pair<std::string, std::vector<std::string>> Cli::CommandSplitter(std::string input) {
    if (input.empty()) throw std::runtime_error("Input no recognized");
    auto splittedInput = StringHelper::split(input, ' ');
    auto cmd = splittedInput.front();
    splittedInput.erase(splittedInput.begin());
    return std::make_pair(cmd, splittedInput);
}