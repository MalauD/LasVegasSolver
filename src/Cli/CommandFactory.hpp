#include "BaseCommand.hpp"
#include "StatusCommand.hpp"
#include "PrintCommand.hpp"
#include "StartCommand.hpp"
#include "PlayCommand.hpp"
#include "EvalCommand.hpp"
#include "DiceCommand.hpp"
#include "SaveCommand.hpp"
#include "OpenCommand.hpp"
#include "exception"

class CommandFactory {
    public:
        static std::unique_ptr<BaseCommand> GetCommandFromStr(std::string cmd);
};
