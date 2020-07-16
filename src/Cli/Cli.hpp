#include <utility>

#include "BaseCommand.hpp"
#include "CommandFactory.hpp"

class Cli {
    public:
        Cli() = default;
        void Start();
        static std::pair<std::string, std::vector<std::string>> CommandSplitter(std::string input);
};