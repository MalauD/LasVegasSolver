#include "GameSetEvaluator.hpp"

std::map<int, int> GameSetEvaluator::EvalGameSetFor(GameSet Gs, DiceColors DcToEval, int Depth) {
    NodesCount = 0;
    std::map<int, int> EvalForSymbolPlay;

    const auto ds = Gs.GetDiceSetBy(DcToEval);

    const auto PossibleOutcomes = DiceSet::GetPossibleOutcomes(ds);
    std::for_each(PossibleOutcomes.begin(), PossibleOutcomes.end(), [this ,Depth ,&Gs, &DcToEval, &EvalForSymbolPlay](const int &OutcomeSymbol) {
        auto newGs = Gs;
        newGs.PlayFor(DcToEval, OutcomeSymbol);

        std::cout << "Building tree for symbol " << OutcomeSymbol << "\n";
        TreeNode tn = GetNodeFor(newGs, DcToEval, Depth);
        std::cout << "Evaluating tree \n";
        EvalForSymbolPlay.insert({ tn.GetEval(), OutcomeSymbol });
    });
    return EvalForSymbolPlay;
}

TreeNode GameSetEvaluator::GetNodeFor(GameSet Gs, DiceColors dc ,int MaxDepth, int Depth) {
    TreeNode tn = TreeNode(Depth);
    NodesCount++;

    auto nextPlaying = Gs.GetPlayingOrder().GetPlayingNow();

    if (Gs.GetDicesCountBy(nextPlaying) == 0 || Depth == MaxDepth) {
        tn.SetEval(Gs.EvaluateForColor(dc));
        return tn;
    }
    const auto AllCombination = Combinations::CombinationsWithRepetitions(Gs.GetDiceSetBy(nextPlaying).GetDicesCount(), nextPlaying);
    
    std::for_each(AllCombination.begin(), AllCombination.end(), [this, &Gs, Depth, MaxDepth, &tn, &dc](const DiceSet& DiceCombination) {
        const auto PossibleOutComes = DiceSet::GetPossibleOutcomes(DiceCombination);

        std::for_each(PossibleOutComes.begin(), PossibleOutComes.end(), 
            [this, &Gs, &DiceCombination, Depth, MaxDepth, &tn, &dc](const int& OutcomeSymbol) {
                auto CurrentlyPlaying = Gs.GetPlayingOrder().GetPlayingNow();
                auto newGs = Gs;
                newGs.SetDiceSetOf(CurrentlyPlaying, DiceCombination);
                newGs.PlayFor(Gs.GetPlayingOrder().GetPlayingNow(), OutcomeSymbol);
                tn.AddNode(GameSetEvaluator::GetNodeFor(newGs, dc, MaxDepth, Depth + 1));
        });
    });


    return tn;
}