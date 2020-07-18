#include <fstream>

#include "BaseCommand.hpp"
#include "../Helper/GameSetWriter.hpp"
#include "../Core/GameSandBox.hpp"

class SaveCommand : public BaseCommand {
    public:
        void Execute(std::vector<std::string> args) override;
};

