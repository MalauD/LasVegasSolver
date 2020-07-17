#include "CommandFactory.hpp"

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

std::unique_ptr<BaseCommand> CommandFactory::GetCommandFromStr(std::string cmd)
{
    switch (str2int(cmd.c_str()))
    {
        case str2int("status"): return std::unique_ptr<BaseCommand>(new StatusCommand());
        case str2int("print"): return std::unique_ptr<BaseCommand>(new PrintCommand());
        case str2int("start"): return std::unique_ptr<BaseCommand>(new StartCommand());

        default:
            throw std::exception("Command not implemented");
    }
}