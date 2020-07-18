#pragma once
#include <string>
#include <sstream>
#include "StringHelper.hpp"
#include "../Core/GameSet.hpp"

class GameSetWriter {
    public:
        static std::string GetGameSetRepresentation(GameSet gs);
        static GameSet GetGameSetFromStr(std::string);
};