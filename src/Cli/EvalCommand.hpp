#include <chrono>
#include "BaseCommand.hpp"
#include "../Core/GameSandBox.hpp"
#include "../Eval/GameSetEvaluator.hpp"

class EvalCommand : public BaseCommand {
    public:
        void Execute(std::vector<std::string> args) override;
};

