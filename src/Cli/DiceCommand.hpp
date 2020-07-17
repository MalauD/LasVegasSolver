#include "BaseCommand.hpp"
#include "../Core/GameSandBox.hpp"

class DiceCommand : public BaseCommand {
    public:
        void Execute(std::vector<std::string> args) override;
};

