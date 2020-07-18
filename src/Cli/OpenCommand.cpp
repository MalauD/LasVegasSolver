#include "OpenCommand.hpp"

void OpenCommand::Execute(std::vector<std::string> args) {
    if (args.empty()) {
        throw std::runtime_error("No argument specified to open command");
        return;
    }
    if (args.size() != 1) {
        throw std::runtime_error("Expected 1 arguments for the start command. Example open out.lvs");
        return;
    }
    
    std::ifstream lvsFileOut;
    lvsFileOut.open(args[0]);
    std::string line;
    std::getline(lvsFileOut, line);
    if (line.empty()) throw std::runtime_error("File specified is empty");
    auto newGs = GameSetWriter::GetGameSetFromStr(line);
    GameSandBox::getInstance().GetGameSet().ResetTo(newGs.GetCasinos(), newGs.GetDiceSets(), newGs.GetPlayingOrder());
}
