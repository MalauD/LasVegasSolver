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
    size_t pos = 0;
    std::vector<std::string> tokens;
    std::string delimiter = " ";
    while ((pos = input.find(delimiter)) != std::string::npos) {
        tokens.push_back(input.substr(0, pos));
        input.erase(0, pos + delimiter.length());
    }
    std::string cmd;
    if (tokens.empty()) cmd = input;
    else {
        cmd = tokens.front();
        tokens.erase(tokens.begin());
    }
    return std::make_pair(cmd, tokens);
}