#include "BaseCommand.hpp"


class StatusCommand : public BaseCommand {
    public:
        void Execute(std::vector<std::string> args) override;
};

