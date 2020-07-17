#pragma once
#include "GameSet.hpp"

class GameSandBox
{
    public:
        static GameSandBox& getInstance()
        {
            static GameSandBox instance;
            return instance;
        }
    private:
        GameSandBox() {};
        GameSet m_gameSet;
    public:
        GameSandBox(GameSandBox const&) = delete;
        void operator=(GameSandBox const&) = delete;
        GameSet& GetGameSet() {
            return m_gameSet;
        }
};