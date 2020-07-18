#include "SaveCommand.hpp"

void SaveCommand::Execute(std::vector<std::string> args) {
    if (args.empty()) {
        throw std::runtime_error("No argument specified to save command");
        return;
    }
    if (args.size() != 1) {
        throw std::runtime_error("Expected 1 arguments for the start command. Example save out.lvs");
        return;
    }
    auto rep = GameSetWriter::GetGameSetRepresentation(GameSandBox::getInstance().GetGameSet());
    std::cout << "Writing " << rep << " to file " << args[0] << "\n";

    std::ofstream outRep(args[0].c_str());
    outRep << rep;
    outRep.close();
}
