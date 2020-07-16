#pragma once
#include <vector>
#include <string>
#include <iostream>

class BaseCommand {
    public:
        virtual void Execute(std::vector<std::string> args) = 0;
};