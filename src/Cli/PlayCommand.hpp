#include "BaseCommand.hpp"
#include "../Core/GameSandBox.hpp"

class PlayCommand : public BaseCommand {
    public:
        void Execute(std::vector<std::string> args) override;
};

