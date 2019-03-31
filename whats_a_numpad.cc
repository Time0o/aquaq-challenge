#include <cstdlib>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>


static std::vector<std::string> const keys {
    " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};


int main()
{
    std::regex reg(R"((\d) (\d))");
    std::cmatch cm;

    std::string line;
    std::stringstream ss;

    while (getline(std::cin, line)) {
        if (std::cin.bad()) {
            std::cerr << "failed to read input\n";
            exit(EXIT_FAILURE);
        }

        if (!regex_match(line.c_str(), cm, reg)) {
            std::cerr << "failed to parse '" << line << "'\n";
            exit(EXIT_FAILURE);
        }

        ss << keys[std::stoi(cm[1])][std::stoi(cm[2]) - 1];
    }

    std::cout << ss.str() << '\n';

    exit(EXIT_SUCCESS);
}
