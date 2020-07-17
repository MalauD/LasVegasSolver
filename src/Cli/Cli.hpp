#include <utility>
#include <sstream>
#include "BaseCommand.hpp"
#include "CommandFactory.hpp"
#include "../Helper/StringHelper.hpp"

class Cli {
    public:
        Cli() = default;
        void Start();
        static std::pair<std::string, std::vector<std::string>> CommandSplitter(std::string input);
};