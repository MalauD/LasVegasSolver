#include "BaseCommand.hpp"
#include "StatusCommand.hpp"
#include "exception"

class CommandFactory {
    public:
        static std::unique_ptr<BaseCommand> GetCommandFromStr(std::string cmd);
};
