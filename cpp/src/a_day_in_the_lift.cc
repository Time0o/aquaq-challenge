#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>


static std::regex const row_reg(R"((\d+) (\d+))");


int main()
{
    std::vector<std::pair<int, int>> instructions;

    // parse input
    std::string line;
    while(std::getline(std::cin, line)) {
        std::cmatch cm;
        if (!std::regex_match(line.c_str(), cm, row_reg)) {
            std::cerr << "failed to parse '" << line << "'\n";
            exit(EXIT_FAILURE);
        }

        int direction = std::stoi(cm[1]);
        int floors = std::stoi(cm[2]);

        instructions.push_back({direction, floors});
    }

    if (std::cin.bad()) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    // move elevator
    int current_floor = 0u;
    bool up = true;

    int i = 1;
    while (current_floor >= 0
           && current_floor < static_cast<int>(instructions.size())) {

        if (instructions[current_floor].first == 0)
            up = !up;

        current_floor += (up ? 1 : -1) * instructions[current_floor].second;

        ++i;
    }

    std::cout << i << '\n';

    exit(EXIT_SUCCESS);
}
