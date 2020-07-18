#include "EvalCommand.hpp"

void EvalCommand::Execute(std::vector<std::string> args) {
    if(args.empty()){
        throw std::runtime_error("No argument specified to eval command");
        return;
    }
    if(args.size() != 1){
        throw std::runtime_error("Expected 1 argument for the eval command");
        return;
    }

    auto depth = std::atoi(args[0].c_str());

    GameSetEvaluator gse;
    auto& gs = GameSandBox::getInstance().GetGameSet();

    if(gs.GetCasinos().size() == 0 || gs.GetDiceSets().size() == 0) throw std::runtime_error("Cannot eval on undefined game set.");

    auto colorPlaying = gs.GetPlayingOrder().GetPlayingNow();
    std::cout << "Evaluating for " << AllDiceColorsPrintable[std::distance(AllDiceColors.begin(), std::find(AllDiceColors.begin(), AllDiceColors.end(), colorPlaying))];
    std::cout << " with a depth of " << depth << "\n";
    auto t1 = std::chrono::high_resolution_clock::now();
    auto res = gse.EvalGameSetFor(gs, colorPlaying, depth);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "Done in "<< duration << " ms with " << gse.NodesCount << " nodes ("<< (float)gse.NodesCount / (float)(duration) <<" N/ms)\n";

    std::for_each(res.begin(), res.end(), [](const std::pair<int, int>& resFor) {
        std::cout << "Eval for casino n " << resFor.second << " -> " << resFor.first << "\n";
        });
}
