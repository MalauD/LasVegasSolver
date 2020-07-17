#include "BaseCommand.hpp"
#include "../Core/GameSandBox.hpp"

class PrintCommand : public BaseCommand {
    public:
        void Execute(std::vector<std::string> args) override;
};

