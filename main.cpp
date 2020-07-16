#include <iostream>
#include <chrono>

#include "src/Core/GameSet.hpp"
#include "src/Core/PlayingOrder.hpp"
#include "src/Eval/GameSetEvaluator.hpp"
#include "src/Helper/Combinations.hpp"

int main() {
    Casino c1 = Casino({Ticket(TicketValues::t80k)}, 1);
    Casino c2 = Casino({Ticket(TicketValues::t50k), Ticket(TicketValues::t30k)}, 2);
    Casino c3 = Casino({Ticket(TicketValues::t60k), Ticket(TicketValues::t20k)}, 3);
    Casino c4 = Casino({Ticket(TicketValues::t90k), Ticket(TicketValues::t10k)}, 4);
    Casino c5 = Casino({ Ticket(TicketValues::t70k) }, 5);
    Casino c6 = Casino({Ticket(TicketValues::t80k)}, 6);

    std::vector<Casino> Sample = {c1, c2, c3, c4, c5, c6};
    std::for_each(Sample.begin(), Sample.end(), [](const Casino& c) {
        std::cout << c;
    });
    
    DiceSet ds1 = DiceSet(4,DiceColors::Black,5);
    DiceSet ds3 = DiceSet({
        Dice(DiceColors::Green,4),
        Dice(DiceColors::Green,6)
    });

    auto po = PlayingOrder({ DiceColors::Black , DiceColors::Green }, DiceColors::Green);

    GameSet gs = GameSet(Sample, { ds1, ds3 }, po);
    //gs.PlayFor(DiceColors::Blue, 5);

    GameSetEvaluator gse = GameSetEvaluator();

    auto t1 = std::chrono::high_resolution_clock::now();
    auto res = gse.EvalGameSetFor(gs, DiceColors::Green, 4);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "Done in "<< duration << " ms with " << gse.NodesCount << " nodes ("<< (float)gse.NodesCount / (float)(duration) <<" N/ms)\n";

    std::for_each(res.begin(), res.end(), [](const std::pair<int, int>& resFor) {
        std::cout << "Eval for casino n " << resFor.second << " -> " << resFor.first << "\n";
        });
    /*
    auto p = PlayingOrder({ DiceColors::Blue, DiceColors::Black, DiceColors::Red }, DiceColors::Red);
    auto e = p.EstimatePlayingIn(2);
    auto e2 = p.Advance(2);
    auto e3 = p.GetPlayingNow();*/


    //auto all = Combinations::CombinationsWithRepetitions(8, DiceColors::Blue);
    char c;
    std::cin>>c;
}