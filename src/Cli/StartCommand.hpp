#include <cstdlib>

#include "BaseCommand.hpp"
#include "../Core/GameSandBox.hpp"
#include "../Helper/StringHelper.hpp"

class StartCommand : public BaseCommand {
    public:
        void Execute(std::vector<std::string> args) override;
};

