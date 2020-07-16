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

        
        default:
            throw std::exception("Command not implemented");
    }
}